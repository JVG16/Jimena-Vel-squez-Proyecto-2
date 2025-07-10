#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype> // para toupper
#include <algorithm> // para transform

using namespace std;

struct Student {
    string id;
    string fullName;
    string province;
    string canton;
    string district;
    int age;
    int gender;
};

struct Grade {
    string studentId;
    string course;
    float project1;
    float project2;
    float essay;
    float forum;
    float defense;
    float average;
    string status;
};

// Función para convertir a mayúsculas
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Función para buscar estudiante por ID
bool studentExists(const vector<Student>& students, const string& id) {
    for (const auto& student : students) {
        if (student.id == id) {
            return true;
        }
    }
    return false;
}

// Función para leer estudiantes desde archivo
vector<Student> readStudentsFromFile(const string& filename) {
    vector<Student> students;
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return students;
    }

    Student temp;
    while (getline(inFile, temp.id)) {
        getline(inFile, temp.fullName);
        getline(inFile, temp.province);
        getline(inFile, temp.canton);
        getline(inFile, temp.district);
        inFile >> temp.age;
        inFile >> temp.gender;
        inFile.ignore(); // Para ignorar el salto de línea

        students.push_back(temp);
    }

    inFile.close();
    return students;
}

// Función para guardar calificaciones en archivo
void saveGradesToFile(const vector<Grade>& grades, const string& filename) {
    ofstream outFile(filename, ios::app); // Modo append

    if (!outFile.is_open()) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        return;
    }

    for (const auto& grade : grades) {
        outFile << grade.studentId << "\n"
                << grade.course << "\n"
                << grade.project1 << "\n"
                << grade.project2 << "\n"
                << grade.essay << "\n"
                << grade.forum << "\n"
                << grade.defense << "\n"
                << grade.average << "\n"
                << grade.status << "\n";
    }

    outFile.close();
}

// Función para ingresar calificaciones
void enterGrades() {
    vector<Student> students = readStudentsFromFile("ESTUDIANTE.txt");
    vector<Grade> grades;

    char option;
    do {
        string studentId;
        cout << "\nIngrese la identificacion del estudiante: ";
        cin >> studentId;
        cin.ignore(); // Limpiar buffer

        if (!studentExists(students, studentId)) {
            cout << "Estudiante no registrado" << endl;

            do {
                cout << "Desea ingresar otra identificacion? (S/N): ";
                cin >> option;
                cin.ignore();
                option = toupper(option);

                if (option != 'S' && option != 'N') {
                    cout << "Opcion no valida. Intente de nuevo." << endl;
                }
            } while (option != 'S' && option != 'N');

            if (option == 'N') {
                return; // Volver al menú principal
            }
            continue; // Volver a solicitar ID
        }

        Grade newGrade;
        newGrade.studentId = studentId;

        // Solicitar materia (no puede estar vacía)
        do {
            cout << "Ingrese la materia que cursa el estudiante: ";
            getline(cin, newGrade.course);

            if (newGrade.course.empty()) {
                cout << "Este campo no puede estar vacio. Intente de nuevo." << endl;
            }
        } while (newGrade.course.empty());

        // Solicitar notas (validar que estén entre 0 y 10)
        cout << "\nIngrese las notas en base 10:" << endl;

        do {
            cout << "Proyecto 1 (0-10): ";
            cin >> newGrade.project1;
            if (newGrade.project1 < 0 || newGrade.project1 > 10) {
                cout << "Nota no valida. Debe estar entre 0 y 10." << endl;
            }
        } while (newGrade.project1 < 0 || newGrade.project1 > 10);

        do {
            cout << "Proyecto 2 (0-10): ";
            cin >> newGrade.project2;
            if (newGrade.project2 < 0 || newGrade.project2 > 10) {
                cout << "Nota no valida. Debe estar entre 0 y 10." << endl;
            }
        } while (newGrade.project2 < 0 || newGrade.project2 > 10);

        do {
            cout << "Ensayo (0-10): ";
            cin >> newGrade.essay;
            if (newGrade.essay < 0 || newGrade.essay > 10) {
                cout << "Nota no valida. Debe estar entre 0 y 10." << endl;
            }
        } while (newGrade.essay < 0 || newGrade.essay > 10);

        do {
            cout << "Foro (0-10): ";
            cin >> newGrade.forum;
            if (newGrade.forum < 0 || newGrade.forum > 10) {
                cout << "Nota no valida. Debe estar entre 0 y 10." << endl;
            }
        } while (newGrade.forum < 0 || newGrade.forum > 10);

        do {
            cout << "Defensa (0-10): ";
            cin >> newGrade.defense;
            if (newGrade.defense < 0 || newGrade.defense > 10) {
                cout << "Nota no valida. Debe estar entre 0 y 10." << endl;
            }
        } while (newGrade.defense < 0 || newGrade.defense > 10);

        // Calcular promedio
        newGrade.average = (newGrade.project1 + newGrade.project2 + newGrade.essay +
                           newGrade.forum + newGrade.defense) / 5.0f;

        // Determinar estado
        if (newGrade.average >= 70) {
            newGrade.status = "Aprobo";
        } else if (newGrade.average >= 50) {
            newGrade.status = "Reposicion";
        } else {
            newGrade.status = "Reprobo";
        }

        grades.push_back(newGrade);

        // Preguntar si desea ingresar otra calificación
        do {
            cout << "\nDesea ingresar calificaciones para otro estudiante? (S/N): ";
            cin >> option;
            cin.ignore();
            option = toupper(option);

            if (option != 'S' && option != 'N') {
                cout << "Opcion no valida. Intente de nuevo." << endl;
            }
        } while (option != 'S' && option != 'N');

    } while (option == 'S');

    // Guardar todas las calificaciones en el archivo
    saveGradesToFile(grades, "CALIFICACIONES.txt");
    cout << "Calificaciones guardadas exitosamente." << endl;
}

// Menú principal (ejemplo)
int main() {
    enterGrades();
    return 0;
}
