#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

template <typename T> using vec = std::vector<T>;
using str = std::string;
using uint = unsigned int;
using uchar = unsigned char;
using std::cin;
using std::cout;
using std::endl;
using std::left;
using std::setw;

const str RST = "\033[0m";
const str BLD = "\033[1m";
const str UND = "\033[4m";
const str INV = "\033[7m";
const str RED = "\033[91m";
const str GRN = "\033[92m";
const str YLW = "\033[93m";
const str BLU = "\033[94m";
const str CYA = "\033[96m";

namespace ID {
static uint Student = 1;
static uint Discipline = 1;
static uint Mark = 1;
void Reset() {
  Student = 1;
  Discipline = 1;
  Mark = 1;
}
} // namespace ID

enum mark : uchar {
  ABSENT = 0,
  PRESENT = 1,
  TWO = 2,
  THREE = 3,
  FOUR = 4,
  FIVE = 5,
};

struct Stats {
  vec<mark> Marks;
  vec<uint> Ids;
  double Average;
  double Attendance;
  uint Count;
  uint CountM;
  uint Missed;

  ~Stats() {
    Marks.clear();
    Ids.clear();
  }
};

class Object {
protected:
  uint Id;
  void SetId(uint id) { this->Id = id; }

public:
  uint GetId() { return this->Id; }
  friend class Menu;
};

class Discipline : public Object {
private:
  str Name;

public:
  Discipline() {
    this->Id = ID::Discipline++;
    this->Name = "";
  }
  Discipline(str name) {
    this->Id = ID::Discipline++;
    this->Name = name;
  }
  str GetName() { return this->Name; }
  void SetName(str name) { this->Name = name; }
};

class Student : public Object {
private:
  str FirstName;
  str LastName;

public:
  Student() {
    this->Id = ID::Student++;
    this->FirstName = "";
    this->LastName = "";
  }
  Student(str first_name, str last_name) {
    this->Id = ID::Student++;
    this->FirstName = first_name;
    this->LastName = last_name;
  }
  str GetName() { return this->FirstName + " " + this->LastName; }
  void SetName(str first_name, str last_name) {
    this->FirstName = first_name;
    this->LastName = last_name;
  }
};

class Mark : public Object {
private:
  uint DisciplineId;
  uint StudentId;
  mark Value;

public:
  Mark() {
    this->Id = ID::Mark++;
    this->DisciplineId = 0;
    this->StudentId = 0;
    this->Value = ABSENT;
  }
  Mark(uint discipline_id, uint student_id, uchar mark) {
    this->Id = ID::Mark++;
    this->DisciplineId = discipline_id;
    this->StudentId = student_id;
    this->Value = (enum mark)(mark % 6);
  }
  uint GetDisciplineId() { return this->DisciplineId; }
  uint GetStudentId() { return this->StudentId; }
  enum mark GetValue() { return this->Value; }
  void SetValue(uchar mark) { this->Value = (enum mark)(mark % 6); }
};

class Journal {
private:
  vec<Discipline> Disciplines;
  vec<Student> Students;
  vec<Mark> Marks;

  vec<Discipline>::iterator FindDiscipline(uint id) {
    vec<Discipline>::iterator itr = this->Disciplines.begin();
    for (; itr < this->Disciplines.end(); itr++)
      if (itr->GetId() == id)
        break;
    return itr;
  }

  bool IsDiscipline(uint id) {
    return (this->Disciplines.end() != this->FindDiscipline(id));
  }

  vec<Student>::iterator FindStudent(uint id) {
    vec<Student>::iterator itr = this->Students.begin();
    for (; itr < this->Students.end(); itr++)
      if (itr->GetId() == id)
        break;
    return itr;
  }

  bool IsStudent(uint id) {
    return (this->Students.end() != this->FindStudent(id));
  }

  vec<Mark>::iterator FindMark(uint id) {
    vec<Mark>::iterator itr = this->Marks.begin();
    for (; itr < this->Marks.end(); itr++)
      if (itr->GetId() == id)
        break;
    return itr;
  }

  bool IsMark(uint id) { return (this->Marks.end() != this->FindMark(id)); }

  vec<Discipline>::iterator FindDiscipline(str name) {
    vec<Discipline>::iterator itr = this->Disciplines.begin();
    for (; itr < this->Disciplines.end(); itr++)
      if (itr->GetName() == name)
        break;
    return itr;
  }

  bool IsDiscipline(str name) {
    return (this->Disciplines.end() != this->FindDiscipline(name));
  }

  vec<Student>::iterator FindStudent(str first_name, str last_name) {
    vec<Student>::iterator itr = this->Students.begin();
    for (; itr < this->Students.end(); itr++)
      if (itr->GetName() == first_name + " " + last_name)
        break;
    return itr;
  }

  bool IsStudent(str first_name, str last_name) {
    return (this->Students.end() != this->FindStudent(first_name, last_name));
  }

  void ClearMarksOnDisciplineDelete(uint d_id) {
    vec<Mark>::iterator itr = this->Marks.begin();
    for (; itr < this->Marks.end(); itr++)
      if (itr->GetDisciplineId() == d_id)
        this->Marks.erase(itr--);
  }

  void ClearMarksOnStudentDelete(uint s_id) {
    vec<Mark>::iterator itr = this->Marks.begin();
    for (; itr < this->Marks.end(); itr++)
      if (itr->GetStudentId() == s_id)
        this->Marks.erase(itr--);
  }

public:
  Journal() {
    this->Disciplines = vec<Discipline>();
    this->Students = vec<Student>();
    this->Marks = vec<Mark>();
  }

  ~Journal() {
    this->Disciplines.clear();
    this->Students.clear();
    this->Marks.clear();
  }

  int ClearAll() {
    this->Disciplines.clear();
    this->Students.clear();
    this->Marks.clear();
    return 0;
  }

  int NewDiscipline(str name) {
    if (IsDiscipline(name))
      return 1;
    this->Disciplines.emplace_back(name);
    return 0;
  }

  int NewStudent(str first_name, str last_name) {
    if (IsStudent(first_name, last_name))
      return 1;
    this->Students.emplace_back(first_name, last_name);
    return 0;
  }

  int NewMark(uint d_id, uint s_id, uint val) {
    if (!IsDiscipline(d_id) || !IsStudent(s_id))
      return 1;
    this->Marks.emplace_back(d_id, s_id, val);
    return 0;
  }

  int DeleteDiscipline(uint d_id) {
    if (!IsDiscipline(d_id))
      return 1;
    this->ClearMarksOnDisciplineDelete(d_id);
    this->Disciplines.erase(FindDiscipline(d_id));
    return 0;
  }

  int DeleteStudent(uint s_id) {
    if (!IsStudent(s_id))
      return 1;
    this->ClearMarksOnStudentDelete(s_id);
    this->Students.erase(FindStudent(s_id));
    return 0;
  }

  int DeleteMark(uint m_id) {
    if (!IsMark(m_id))
      return 1;
    this->Marks.erase(FindMark(m_id));
    return 0;
  }

  int RenameDiscipline(uint d_id, str name) {
    if (!IsDiscipline(d_id) || IsDiscipline(name))
      return 1;
    this->FindDiscipline(d_id)->SetName(name);
    return 0;
  }

  int RenameStudent(uint s_id, str first_name, str last_name) {
    if (!IsStudent(s_id) || IsStudent(first_name, last_name))
      return 1;
    this->FindStudent(s_id)->SetName(first_name, last_name);
    return 0;
  }

  int ChangeMark(uint m_id, uchar mark) {
    if (!IsMark(m_id))
      return 1;
    this->FindMark(m_id)->SetValue(mark);
    return 0;
  }

  int GetStats(Stats &st, uint d_id, uint s_id) {
    if (!IsDiscipline(d_id) || !IsStudent(s_id))
      return 1;
    double sum{0};
    uint count{0}, missed{0}, marks_count{0};
    vec<Mark>::iterator itr = this->Marks.begin();
    for (; itr < this->Marks.end(); itr++) {
      if (itr->GetDisciplineId() != d_id || itr->GetStudentId() != s_id)
        continue;
      st.Marks.emplace_back(itr->GetValue());
      st.Ids.emplace_back(itr->GetId());
      switch (itr->GetValue()) {
      case mark::ABSENT:
        missed++;
        count++;
        break;
      case mark::PRESENT:
        count++;
        break;
      case mark::TWO:
        sum += (double)mark::TWO;
        marks_count++;
        count++;
        break;
      case mark::THREE:
        sum += (double)mark::THREE;
        marks_count++;
        count++;
        break;
      case mark::FOUR:
        sum += (double)mark::FOUR;
        marks_count++;
        count++;
        break;
      case mark::FIVE:
        sum += (double)mark::FIVE;
        marks_count++;
        count++;
        break;
      default:
        break;
      }
    }
    st.Count = count;
    st.CountM = marks_count;
    st.Missed = missed;
    st.Attendance = (double)(count - missed) / (double)count;
    st.Average = sum / marks_count;
    return 0;
  }

  friend class Menu;
};

class Menu {
private:
  const str GREETING = "Press <Enter> and type 'help' for more info!";
  const str PROMPT = GRN + "$ " + RST;
  const str LIST_HEADER_STYLE = CYA;
  const str HELP_HEADER_STYLE = CYA;
  const str HELP_KEY_STYLE = INV;
  const str HELP_ACTION_STYLE = BLD;
  const str HELP_EXAMPLE_STYLE = GRN;
  Journal journal;

  enum ACTION : char {
    QUIT = 'q',
    HELP = 'h',
    CLEAR_SCREEN = 'c',
    CLEAR_DATABASE = 'X',
    NEW_DISCIPLINE = 'N',
    NEW_STUDENT = 'n',
    DELETE_DISCIPLINE = 'D',
    DELETE_STUDENT = 'd',
    RENAME_DISCIPLINE = 'R',
    RENAME_STUDENT = 'r',
    LIST_DISCIPLINES = 'L',
    LIST_STUDENTS = 'l',
    SET_MARK = 'm',
    DELETE_MARK = 'x',
    CHANGE_MARK = 'v',
    SHOW_MARKS = 's',
    RESOLVE_INDEXES = 'i',
  };

  void ClearScreen() { system("clear"); }
  void PrintRed(str message) { cout << RED << message << RST << endl; }
  void PrintGreen(str message) { cout << GRN << message << RST << endl; }
  void PrintYellow(str message) { cout << YLW << message << RST << endl; }
  void FlushInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  void PrintMark(mark mark, str delimiter = "   ") {
    str style;
    char symbol;
    switch (mark) {
    case mark::ABSENT:
      style = INV + BLD + RED;
      symbol = 'H';
      break;
    case mark::PRESENT:
      style = INV + BLD + GRN;
      symbol = 'V';
      break;
    case mark::TWO:
      style = BLD + RED;
      symbol = '2';
      break;
    case mark::THREE:
      style = BLD + YLW;
      symbol = '3';
      break;
    case mark::FOUR:
      style = BLD + GRN;
      symbol = '4';
      break;
    case mark::FIVE:
      style = BLD + GRN;
      symbol = '5';
      break;
    default:
      break;
    }
    cout << style << symbol << RST << delimiter;
  }

  bool Confirm(str question = "Confirm?") {
    FlushInputBuffer();
    char response;
    cout << question;
    cout << " [" << GRN << 'y' << RST << '/' << RED << 'n' << RST << "] ";
    cin >> response;
    return response == 'y';
  }

  void DrawListHeader(str obj) {
    cout << LIST_HEADER_STYLE;
    cout << "[ID]\t" << '[' << obj << ']';
    cout << RST << endl;
  }

  void DrawHelpHeader() {
    cout << HELP_HEADER_STYLE << left << setw(8) << "[key]" << '\t' << left
         << setw(40) << "[action]" << left << setw(32) << "[example]" << RST
         << endl;
  }

  void DrawHelpRow(str key, str action, str example) {
    cout << left << setw(8) << HELP_KEY_STYLE + key + RST << '\t' << left
         << setw(40) << HELP_ACTION_STYLE + action + RST << left << setw(32)
         << PROMPT + HELP_EXAMPLE_STYLE + example + RST << endl;
  }

  void DrawLine(char ch = '-', str style = CYA, uint length = 80) {
    cout << RST << style;
    for (int i = 0; i < length; i++)
      cout << ch;
    cout << RST << endl;
  }

  void ShowHelp() {
    DrawLine();
    DrawHelpHeader();
    DrawHelpRow("[h]", "Show help", "h");
    DrawHelpRow("[q]", "Quit", "q");
    DrawHelpRow("[c]", "Clear the screen", "c");
    DrawHelpRow("[X]", "Clear all data", "X");
    DrawHelpRow("[N]", "Add new discipline", "N <name>");
    DrawHelpRow("[n]", "Add new student", "n <first_name> <last_name>");
    DrawHelpRow("[D]", "Delete a discipline", "D <d_id>");
    DrawHelpRow("[d]", "Delete a student", "d <s_id>");
    DrawHelpRow("[R]", "Rename a discipline", "R <d_id> <new_name>");
    DrawHelpRow("[r]", "Rename a student", "r <s_id> <new_fn> <new_ln>");
    DrawHelpRow("[L]", "List all disciplines", "L");
    DrawHelpRow("[l]", "List all students", "l");
    DrawHelpRow("[m]", "Set new mark", "m <d_id> <s_id> <mark>");
    DrawHelpRow("[s]", "Show marks and statistics", "s <d_id> <s_id>");
    DrawHelpRow("[x]", "Delete a mark", "x <m_id>");
    DrawHelpRow("[v]", "Change a mark", "v <m_id> <mark>");
    DrawHelpRow("[i]", "Resolve all IDs", "i");
    DrawLine();
    cout << "Available marks: 0=Absent, 1=Present, 2-5" << endl;
    DrawLine();
  }

  void ClearDatabase() {
    if (!Confirm("Clear all data?"))
      return;
    journal.ClearAll();
    ID::Reset();
    PrintRed("Database has been cleared!");
  }

  void NewDiscipline() {
    str name;
    cin >> name;
    if (journal.NewDiscipline(name))
      return;
    PrintGreen("Discipline added!");
  }

  void NewStudent() {
    str first_name, last_name;
    cin >> first_name >> last_name;
    if (journal.NewStudent(first_name, last_name))
      return;
    PrintGreen("Student added!");
  }

  void DeleteDiscipline() {
    uint d_id;
    cin >> d_id;
    if (!journal.IsDiscipline(d_id))
      return;
    if (!Confirm("Delete discipline?"))
      return;
    if (journal.DeleteDiscipline(d_id))
      return;
    PrintRed("Discipline deleted!");
  }

  void DeleteStudent() {
    uint s_id;
    cin >> s_id;
    if (!journal.IsStudent(s_id))
      return;
    if (!Confirm("Delete student?"))
      return;
    if (journal.DeleteStudent(s_id))
      return;
    PrintRed("Student deleted!");
  }

  void RenameDiscipline() {
    uint d_id;
    str name;
    cin >> d_id >> name;
    if (!journal.IsDiscipline(d_id))
      return;
    if (!Confirm("Rename discipline?"))
      return;
    if (journal.RenameDiscipline(d_id, name))
      return;
    PrintYellow("Discipline renamed!");
  }

  void RenameStudent() {
    uint s_id;
    str first_name, last_name;
    cin >> s_id >> first_name >> last_name;
    if (!journal.IsStudent(s_id))
      return;
    if (!Confirm("Rename student?"))
      return;
    if (journal.RenameStudent(s_id, first_name, last_name))
      return;
    PrintYellow("Student renamed!");
  }

  void ListDisciplines() {
    vec<Discipline>::iterator itr = journal.Disciplines.begin();
    vec<Discipline>::iterator end = journal.Disciplines.end();
    if (itr == end) {
      PrintRed("No disciplines found!");
      return;
    }
    DrawLine();
    DrawListHeader("Discipline");
    for (; itr < end; itr++)
      cout << itr->GetId() << '\t' << itr->GetName() << endl;
    DrawLine();
  }

  void ListStudents() {
    vec<Student>::iterator itr = journal.Students.begin();
    vec<Student>::iterator end = journal.Students.end();
    if (itr == end) {
      PrintRed("No students found!");
      return;
    }
    DrawLine();
    DrawListHeader("Student");
    for (; itr < end; itr++)
      cout << itr->GetId() << '\t' << itr->GetName() << endl;
    DrawLine();
  }

  void SetMark() {
    uint d_id, s_id, val;
    cin >> d_id >> s_id >> val;
    if (journal.NewMark(d_id, s_id, val))
      return;
    PrintGreen("Mark added!");
  }

  void DeleteMark() {
    uint m_id;
    cin >> m_id;
    if (!journal.IsMark(m_id))
      return;
    if (!Confirm("Delete mark?"))
      return;
    if (journal.DeleteMark(m_id))
      return;
    PrintRed("Mark deleted!");
  }

  void ChangeMark() {
    uint m_id, val;
    cin >> m_id >> val;
    if (!journal.IsMark(m_id))
      return;
    if (!Confirm("Change mark?"))
      return;
    if (journal.ChangeMark(m_id, val))
      return;
    PrintYellow("Mark changed!");
  }

  void ShowMarks() {
    str discipline_name, student_name, style;
    Stats stats;
    uint d_id, s_id;
    cin >> d_id >> s_id;
    if (journal.GetStats(stats, d_id, s_id))
      return;
    discipline_name = journal.FindDiscipline(d_id)->GetName();
    student_name = journal.FindStudent(s_id)->GetName();
    DrawLine();
    cout << "DSC:\t" << CYA << discipline_name << RST << endl;
    cout << "STD:\t" << CYA << student_name << RST << endl;

    if (stats.Count == 0) {
      cout << RED << "\tThere is no marks for this student!" << RST << endl;
      DrawLine();
      return;
    }

    cout << "MKS:\t";
    for (vec<mark>::iterator itr = stats.Marks.begin(); itr < stats.Marks.end();
         itr++)
      PrintMark(*itr);
    cout << endl;

    cout << "IDS:\t";
    for (vec<uint>::iterator itr = stats.Ids.begin(); itr < stats.Ids.end();
         itr++)
      cout << left << setw(4) << *itr;
    cout << endl;

    if (stats.Average >= 2 && stats.Average < 3)
      style = RED;
    else if (stats.Average >= 3 && stats.Average < 4)
      style = YLW;
    else if (stats.Average >= 4 && stats.Average <= 5)
      style = GRN;
    else
      style = CYA;
    if (stats.CountM > 0)
      cout << "AVG:\t" << style << stats.Average << RST + ' ' << '('
           << stats.CountM << ')' << endl;

    if (stats.Attendance >= 0 && stats.Attendance < 0.6)
      style = RED;
    else if (stats.Attendance >= 0.6 && stats.Attendance < 0.85)
      style = YLW;
    else if (stats.Attendance >= 0.85 && stats.Attendance <= 1)
      style = GRN;
    else
      style = CYA;
    cout << "ATD:\t" << style << stats.Attendance * 100 << '%' << RST << endl;

    cout << "MIS:\t" << stats.Missed << '/' << stats.Count << endl;
    DrawLine();
  }

  void ResolveIndexes() {
    if (!Confirm("Resolve IDs?"))
      return;
    uint d_count = journal.Disciplines.size();
    uint s_count = journal.Students.size();
    uint m_count = journal.Marks.size();

    for (int i = 1; i <= d_count; i++)
      journal.Disciplines.at(i - 1).SetId(i);
    for (int i = 1; i <= s_count; i++)
      journal.Students.at(i - 1).SetId(i);
    for (int i = 1; i <= m_count; i++)
      journal.Marks.at(i - 1).SetId(i);

    ID::Discipline = d_count + 1;
    ID::Student = s_count + 1;
    ID::Mark = m_count + 1;

    PrintYellow("IDs resolved!");
  }

public:
  Menu() {}
  void Run() {
    char input;
    ClearScreen();
    cout << GREETING << endl;
    while (true) {
      FlushInputBuffer();
      if (cin.eof())
        break; // Exit on <C-d>
      cout << PROMPT;
      cin >> input;
      switch (input) {
      case ACTION::QUIT:
        if (!Confirm("Quit?"))
          break;
        return;
      case ACTION::HELP:
        ShowHelp();
        break;
      case ACTION::CLEAR_SCREEN:
        ClearScreen();
        break;
      case ACTION::CLEAR_DATABASE:
        ClearDatabase();
        break;
      case ACTION::NEW_DISCIPLINE:
        NewDiscipline();
        break;
      case ACTION::NEW_STUDENT:
        NewStudent();
        break;
      case ACTION::DELETE_DISCIPLINE:
        DeleteDiscipline();
        break;
      case ACTION::DELETE_STUDENT:
        DeleteStudent();
        break;
      case ACTION::RENAME_DISCIPLINE:
        RenameDiscipline();
        break;
      case ACTION::RENAME_STUDENT:
        RenameStudent();
        break;
      case ACTION::LIST_DISCIPLINES:
        ListDisciplines();
        break;
      case ACTION::LIST_STUDENTS:
        ListStudents();
        break;
      case ACTION::SET_MARK:
        SetMark();
        break;
      case ACTION::DELETE_MARK:
        DeleteMark();
        break;
      case ACTION::CHANGE_MARK:
        ChangeMark();
        break;
      case ACTION::SHOW_MARKS:
        ShowMarks();
        break;
      case ACTION::RESOLVE_INDEXES:
        ResolveIndexes();
        break;
      default:
        break;
      }
    }
  }
};

int main(int argc, char *argv[]) {
  Menu menu;
  menu.Run();
  return 0;
}
