#include "Ship.h"


Ship::Ship(unsigned short length) {
    if (!checkLength(length)) {
        std::cerr << "Ship length must be from 1 to 4" << '\n';
        length = 0;
    }
    this->length = length;
    is_vertical = true;
    segments.resize(length);
    for (auto &segment: segments) {
        segment = SegmentState::FULL;
    }
}

bool Ship::checkLength(int length) {
    if (length < 1 || length > 4) {
        return false;
    }
    return true;
}

void Ship::takeDamage(int index) {
    auto &segment = segments[index];
    switch (segment) {
        case SegmentState::FULL:
            segment = SegmentState::Damaged;
            break;
        case SegmentState::Damaged:
            segment = SegmentState::Destroyed;
            break;
        case SegmentState::Destroyed:
            break;
    }

}

void Ship::setIsVertical(bool value) {
    is_vertical = value;
}

bool Ship::isVertical() {
    return is_vertical;
}

bool Ship::isShipDestroyed() {
    for (auto &segment: segments) {
        if (segment == SegmentState::FULL || segment == SegmentState::Damaged)
            return false;
    }
    return true;
}

unsigned short Ship::getLength() {
    return length;
}

SegmentState Ship::getSegmentState(int index) {
    return segments[index];
}

void Ship::setSegmentState(int index, SegmentState state) {
    segments[index] = state;
}



