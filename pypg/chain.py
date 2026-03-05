from typing import Callable


def chain_sum(num: int) -> Callable:
    result: int = num

    def wrapper(num: int | None = None) -> Callable | int:
        nonlocal result
        if num is None:
            return result
        result += num
        return wrapper

    return wrapper


print(chain_sum(5)(4)(7)())
print(chain_sum(-2)(46)())


del chain_sum


class chain_sum(int):
    def __call__(self, num: int = 0):
        return chain_sum(self + num)


print(2 * chain_sum(4)(6))
