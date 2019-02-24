#include "game_board_edit.h"

#include <QMouseEvent>

namespace bigmama
{

void EditableGameBoard::mouseMoveEvent(QMouseEvent *event)
{
  assert(event != nullptr);
  const QPointF& position = event->localPos(); 
}

}
