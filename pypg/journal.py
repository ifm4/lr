from dataclasses import dataclass


@dataclass
class Student:
    name: str
    year: int
    id: int = 0


@dataclass
class Discipline:
    name: str
    hours: int
    id: int = 0


class Journal:
    students: list[Student]
    disciplines: list[Discipline]
    marks: dict

    _student_id = 0
    _discipline_id = 0
    _mark_id = 0

    def __init__(self):
        self.students = []
        self.disciplines = []
        self.marks = {}

    def _is_mark_value_valid(self, value: int) -> bool:
        if not isinstance(value, int):
            raise TypeError()
        return 0 <= value <= 5

    def _is_student_valid(self, student_id: int) -> bool:
        if not isinstance(student_id, int):
            raise TypeError()
        return bool(list(filter(lambda s: s.id == student_id, self.students)))

    def _is_discipline_valid(self, discipline_id: int) -> bool:
        if not isinstance(discipline_id, int):
            raise TypeError()
        return bool(list(filter(lambda d: d.id == discipline_id, self.disciplines)))

    def add_student(self, student: Student) -> int:
        if not isinstance(student, Student):
            raise TypeError()
        self._student_id += 1
        student.id = self._student_id
        self.students.append(student)
        return self._student_id

    def add_discipline(self, discipline: Discipline) -> int:
        if not isinstance(discipline, Discipline):
            raise TypeError()
        self._discipline_id += 1
        discipline.id = self._discipline_id
        self.disciplines.append(discipline)
        return self._discipline_id

    def add_mark(self, student_id: int, discipline_id: int, value: int) -> int | None:
        if not self._is_student_valid(student_id):
            return
        if not self._is_discipline_valid(discipline_id):
            return
        if not self._is_mark_value_valid(value):
            return
        self._mark_id += 1
        self.marks.update(
            {self._mark_id: {"s_id": student_id, "d_id": discipline_id, "val": value}}
        )
        return self._mark_id

    def get_avg_mark(self, student_id: int, discipline_id: int) -> float | None:
        if not self._is_student_valid(student_id):
            return
        if not self._is_discipline_valid(discipline_id):
            return
        selected = [
            mark["val"]
            for mark in self.marks.values()
            if mark["s_id"] == student_id
            and mark["d_id"] == discipline_id
            and mark["val"] > 1
        ]
        if len(selected) == 0:
            return
        return sum(selected) / len(selected)


if __name__ == "__main__":
    students = (
        Student("Alice", 1),
        Student("Bob", 3),
        Student("Charlie", 2),
    )

    disciplines = (
        Discipline("Math", 90),
        Discipline("OS", 45),
        Discipline("Chemistry", 15),
    )

    j = Journal()

    for s in students:
        j.add_student(s)

    for d in disciplines:
        j.add_discipline(d)

    j.add_mark(1, 1, 4)
    j.add_mark(1, 1, 4)
    j.add_mark(1, 1, 4)
    j.add_mark(1, 1, 4)
    j.add_mark(1, 1, 5)
    j.add_mark(1, 1, 4)

    print(j.students)
    print(j.disciplines)
    print(j.marks)
    print(j.get_avg_mark(1, 1))
