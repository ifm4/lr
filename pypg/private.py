class Stupid:
    __x: int
    __y: int

    def __init__(self, x, y):
        self.__x = x
        self.__y = y


s = Stupid(2, 3)
print(dir(s))
