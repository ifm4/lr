import re
import time
from typing import Callable
from functools import wraps


def timeit(func: Callable) -> Callable:
    @wraps(func)
    def wrapper(*args, **kwargs):
        start_time = time.time()
        result = func(*args, **kwargs)
        end_time = time.time()
        dt_mcs = (end_time - start_time) * 1_000_000
        print(f"Completed `{func.__name__}` in {dt_mcs:.3f} μs")
        return result

    return wrapper


@timeit
def clean_smiles_re(text: str) -> str:
    result = re.sub(r":-\)+", "", text)
    return result


@timeit
def clean_smiles_if(text: str) -> str:
    result = ""
    match_len = 0

    def delete_match_and_reset_len(new_len: int = 0) -> None:
        nonlocal result, match_len
        if match_len >= 3:
            result = result[:-match_len]
        match_len = new_len

    for char in text:
        if char == ":":
            delete_match_and_reset_len(1)
        elif char == "-":
            if match_len == 1:
                match_len = 2
            else:
                delete_match_and_reset_len()
        elif char == ")":
            if match_len >= 2:
                match_len += 1
            else:
                match_len = 0
        else:
            delete_match_and_reset_len()
        result += char

    delete_match_and_reset_len()
    return result


def main():
    example_strings = (
        "",
        ":-)",
        ":-)-)",
        ":-):-)",
        ":-))):-)",
        ":-))",
        ":---)):",
        "::-)",
        "sdlf:lfds-sdlf)sdlf",
        ":-)))sd:-dsf:)dlf-)lsdf:-)",
        ":-)))sd:-dsf:)dlf-)lsdf:-):-",
        "sdlj:-)))))sdfl))dfs",
        "sdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdafsdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdafsdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdafsdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdafsdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdafsdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdafsdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdafsdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdafsdlkfjsldjfl;sdfjl;kdjafklsdjaflksdjfslda;jfgsd:-___sd;fjlsdf:-)))))sd;lfjlksdjfk;lsdkjfslkdaf",
    )
    for s in example_strings:
        print(clean_smiles_re(s))
        print(clean_smiles_if(s))
        assert clean_smiles_re(s) == clean_smiles_if(s)
    print("[PASSED]")


if __name__ == "__main__":
    main()
