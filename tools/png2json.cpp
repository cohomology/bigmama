#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>

#define PNG_DEBUG 3
#include <png.h>

class PngReader
{
public:
  PngReader(const char * pngFileName,
            const char * jsonFileName,
            unsigned int gridSize)
    : m_pngFileName{pngFileName}, m_jsonFileName{jsonFileName},
    m_gridSize{gridSize}
  {
    readPngFile();
  }

  ~PngReader()
  {
    for (int y=0; y<m_height; y++)
      free(m_row_pointers[y]);
    free(m_row_pointers);
  }

  void writeJson();
  
private:
  void readPngFile();

  const char * m_pngFileName;
  const char * m_jsonFileName;
  unsigned int m_gridSize;
  int m_width, m_height;
  png_byte m_color_type;
  png_byte m_bit_depth;

  png_structp m_png_ptr;
  png_infop m_info_ptr;
  int m_number_of_passes;
  png_bytep * m_row_pointers;
};

void PngReader::readPngFile()
{
  char header[8];    // 8 is the maximum size that can be checked

  /* open file and test for it being a png */
  FILE *fp = fopen(m_pngFileName, "rb");
  if (!fp)
  {
    std::cerr << "[read_png_file] File " << m_pngFileName << " could not be opened for reading" << std::endl;
    exit(-1);
  }
  fread(header, 1, 8, fp);
  if (png_sig_cmp((png_const_bytep) header, 0, 8))
  {
    std::cerr << "[read_png_file] File " << m_pngFileName << " is no png file" << std::endl;
    exit(-1); 
  }

  /* initialize stuff */
  m_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!m_png_ptr)
  {
    std::cerr << "[read_png_file] png_create_read_struct failed" << std::endl;
    exit(-1);
  }

  m_info_ptr = png_create_info_struct(m_png_ptr);
  if (!m_info_ptr)
  {
    std::cerr << "[read_png_file] png_create_info_struct failed" << std::endl;
    exit(-1);
  }

  if (setjmp(png_jmpbuf(m_png_ptr)))
  {
    std::cerr << "[read_png_file] Error during init_io" << std::endl;
    exit(-1);
  }

  png_init_io(m_png_ptr, fp);
  png_set_sig_bytes(m_png_ptr, 8);

  png_read_info(m_png_ptr, m_info_ptr);

  m_width = png_get_image_width(m_png_ptr, m_info_ptr);
  m_height = png_get_image_height(m_png_ptr, m_info_ptr);
  m_color_type = png_get_color_type(m_png_ptr, m_info_ptr);
  m_bit_depth = png_get_bit_depth(m_png_ptr, m_info_ptr);

  m_number_of_passes = png_set_interlace_handling(m_png_ptr);
  png_read_update_info(m_png_ptr, m_info_ptr);


  /* read file */
  if (setjmp(png_jmpbuf(m_png_ptr)))
  {
    std::cerr << "[read_png_file] Error during read_image" << std::endl;
    exit(-1);
  }

  m_row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * m_height);
  for (int y=0; y<m_height; y++)
    m_row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(m_png_ptr,m_info_ptr));

  png_read_image(m_png_ptr, m_row_pointers);

  fclose(fp);
}

void PngReader::writeJson()
{
  if (png_get_color_type(m_png_ptr, m_info_ptr) == PNG_COLOR_TYPE_RGB)
  {
    std::cerr << "[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
              << "(lacks the alpha channel)" << std::endl;
    exit(-1);
  }

  if (png_get_color_type(m_png_ptr, m_info_ptr) != PNG_COLOR_TYPE_RGBA)
  {
    std::cerr << "[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA ("
              << (int) PNG_COLOR_TYPE_RGBA << ") (is " 
              << png_get_color_type(m_png_ptr, m_info_ptr) 
              << ")" << std::endl;
    exit(-1);
  }

  std::ofstream json(m_jsonFileName);
  if (!json.is_open())
  {
    std::cerr << "Could not open output file: \"" << m_jsonFileName << "\"." << std::endl;
    exit(-1);
  }

  json << "[" << std::endl;

  // very slow algorithm ;-)
  bool first = true;
  for (int x = 0; x < m_width / m_gridSize; ++x)
  {
    for (int y = 0; y < m_height / m_gridSize; ++y)
    {
      bool foundPixel = false;
      for (int xgrid = 0; xgrid < m_gridSize; ++xgrid)
      {
        for (int ygrid = 0; ygrid < m_gridSize; ++ygrid)
        {
          png_byte* row = m_row_pointers[m_gridSize * y + ygrid]; 
          png_byte* ptr = &(row[(m_gridSize * x + xgrid)*4]); 
          if (ptr[0] != 255 || ptr[1] != 255 || ptr[2] != 255)
          {
            foundPixel = true;
            break;
          }
        }
        if (foundPixel)
          break;
      }
      if (foundPixel)
      {
        if (first)
          first = false;
        else
          json << ", " << std::endl;
        json << "     { \"texture\" : 0," << std::endl;
        json << "       \"x\"       : " << x * m_gridSize << "," << std::endl;
        json << "       \"y\"       : " << y * m_gridSize << "," << std::endl; 
        json << "       \"width\"   : " << m_gridSize << "," << std::endl; 
        json << "       \"height\"  : " << m_gridSize << " }";
      }
    }
  }
  json << "]" << std::endl; 
  json.close();
}

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " <png_file> <out_json> <grid_size>" << std::endl;
    exit(-1);
  }
  try
  {
    PngReader reader(argv[1], argv[2], boost::lexical_cast<short>(argv[3]));
    reader.writeJson();
  }
  catch(const boost::bad_lexical_cast&)
  {
    std::cerr << "Please enter a correct number as a grid size" << std::endl;
    exit(-1);
  }
  return 0;
}

