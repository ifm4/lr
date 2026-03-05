from typing import Protocol, runtime_checkable


# duck typing
@runtime_checkable
class Shape2D(Protocol):
    def get_square(self) -> float: ...
    def get_perimeter(self) -> float: ...


class Square:
    def get_square(self):
        print("square of a square")

    def get_perimeter(sefl):
        print("perimeter of a square")


class Rect:
    def get_square(self):
        print("square of a rect")

    def get_perimeter(sefl):
        print("perimeter of a rect")


assert issubclass(Square, Shape2D)
assert issubclass(Rect, Shape2D)
