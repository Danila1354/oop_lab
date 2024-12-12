#include "ConsoleRenderer.h"
void ConsoleRenderer::drawField(GameField& field) {
    for (int i = 0; i < field.getHeight(); i++) {
        for (int j = 0; j < field.getWidth(); j++) {
            Cell cell = field.getCell(j, i);
            drawCell(cell);
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
void ConsoleRenderer::drawCell(Cell& cell){
    bool is_open = cell.isOpen();
    Status status = cell.getStatus();
    if (is_open) {
        if (status == Status::Empty)
            std::cout << "⚪";
        else {
            Ship* pointer_to_ship = cell.getPointerToShip();
            if (pointer_to_ship->isShipDestroyed()) {
                std::cout << "🔥";
                return;
            }
            SegmentState segment_state = pointer_to_ship->getSegmentState(cell.getIndexOfSegment());
            if (segment_state == SegmentState::Damaged) {
                std::cout << u8"\U0001F7E5";
            }
            else if (segment_state == SegmentState::FULL){
                std::cout<<u8"\U0001F6A2";
            }
            else {
                std::cout << "❌";
            }
        }
    } else
        std::cout << "⬜\uFE0F";
}
void ConsoleRenderer::printMessage(const std::string& message){
    std::cout << message << std::endl;
}
