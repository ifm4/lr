class Point:
    x: int
    y: int

    def test(this, x, y):
        this.x = x
        this.y = y


p = Point()
p.test(2, 5)
print(f"{p.x=} {p.y=} {p=}")


class Singleton:
    __instance = None

    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
            cls.__instance = super().__new__(cls)
        return cls.__instance

    def __del__(self):
        Singleton.__instance = None

    def __init__(self, param):
        self.param = param
