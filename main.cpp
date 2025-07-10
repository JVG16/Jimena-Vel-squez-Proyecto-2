#include <iostream>
#include <vector> // Funciones.
#include <string>
#include <fstream> // Archivos.
#include <conio.h>

using namespace std;

// Función

struct Student
{
    string id;
    string fullName;
    string province;
    string canton;
    string district;
    int age;
    int gender;
};

struct Califications
{
    string id;
    string subject;
    float firstProject;
    float secondProject;
    float ensayo;
    float foro;
    float defense;
    float prom;
};

// Función de estudiantes.

void RegistrarEstudiante (vector<Student>&student);
void ModificarDatosEstudiante (vector<Student>&student);
void EliminarRegistroEstudiante (vector<Student>&student);
void ReporteEstudiante (vector<Student>&student);

// Función para las calificaciones.

void IngresarCalificaciones (vector<Califications>&califications);
void ModificarRegistroEstudiante (vector<Califications>&califications);


int main()
{
    setlocale(LC_CTYPE,"Spanish"); //Idioma y carácteres especiales.
    vector <Student>student;
    vector <Califications>califications;
    int option;
    do
    {
        cout << "Menu Principal"<< endl;
        cout << "1.Registrar estudiante."<< endl;
        cout << "2.Ingresar calificaciones en distintas materias." << endl;
        cout << "3.Modificar datos estudiantes." << endl;
        cout << "4.Modificar registo de notas por estudiante." << endl;
        cout << "5.Eliminar registro de estudiante." << endl;
        cout << "6.Reporte de estudiantes, promedios y estado." << endl;
        cout << "7.Salir del programa." << endl;
        cout << "Digite por favor un número del 1-7" << endl;
        cin >> option;
        if (cin.fail())
        {
            cin.clear();
            while (cin.get() != '\n');
        }
        cout << endl;

        switch(option)
        {
        case 1:
        {
            RegistrarEstudiante(student);
            break;
        }
        case 2:
        {
            IngresarCalificaciones(califications);
            break;
        }
        case 3:
        {
            ModificarDatosEstudiante(student);
            break;
        }
        case 4:
        {
            ModificarRegistroEstudiante(califications);
            cout << endl;
            break;
        }
        case 5:
        {
            cout << "Eliminar registro de estudiante." << endl;
            getch();
            cout << endl;
            break;
        }
        case 6:
        {
            cout << "Reporte de estudiantes, promedios y estado." << endl;
            getch();
            cout << endl;
            break;
        }
        case 7:
        {
            cout << "Salir del programa." << endl;
            getch();
            cout << endl;
            break;
            default:
                cout << "Opción no válida" << endl;
            }

        }
    }
    while(option != 7);
    return 0;
}

// Función Registrar Estudiante.

void RegistrarEstudiante(vector<Student>& student)
{
    cout << "-------------------------------------------------------------------"<<endl;
    cout << "|                  REGISTRO DE UN ESTUDIANTE                      |"<< endl;
    cout << "-------------------------------------------------------------------"<<endl;
    getch();
    cout << endl;

    Student add;

    // Identificación.

    bool verification;
    do
    {
        verification = true;
        cout << "Ingrese la identificación del estudiante (10 dígitos): ";
        cin >> add.id;

        if (add.id.length() != 10)
        {
            verification = false;
        }
        else
        {
            for (int i = 0; i < add.id.length(); i++)
            {
                if (add.id[i] < '0' || add.id[i] > '9')
                {
                    verification = false;
                    break;
                }
            }

            bool todosIguales = true;
            for (int i = 1; i < add.id.length(); i++)
            {
                if (add.id[i] != add.id[0])
                {
                    todosIguales = false;
                    break;
                }
            }
            if (todosIguales)
            {
                verification = false;
            }
        }

        if (!verification)
        {
            cout << "Error: debe ingresar 10 números y que no se repitan." << endl;
        }

    }
    while (!verification);

    cin.ignore();
    getch();
    cout << endl;

    // Nombre completo
    do
    {
        verification = true;
        cout << "Ingrese el nombre completo (nombre y apellidos): ";
        getline(cin, add.fullName);

        for (int i = 0; i < add.fullName.length(); i++)
        {
            if (!isalpha(add.fullName[i]) && add.fullName[i] != ' ')
            {
                verification = false;
                break;
            }
        }

        if (!verification || add.fullName.length() == 0)
        {
            cout << "Error: solo debe ingresar letras y espacios." << endl;
        }

    }
    while (!verification || add.fullName.length() == 0);

    getch();
    cout << endl;

    // Residencia
    cout << "Ingrese el lugar de residencia:" << endl;
    cout << "- Provincia: ";
    getline(cin, add.province);
    cout << "- Cantón: ";
    getline(cin, add.canton);
    cout << "- Distrito: ";
    getline(cin, add.district);

    getch();
    cout << endl;

    // Edad
    do
    {
        verification = true;
        cout << "Ingrese la edad (18-100): ";
        cin >> add.age;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Error: debe ingresar un número válido." << endl;
            verification = false;
        }

        if (add.age < 18 || add.age > 100)
        {
            cout << "Error: la edad debe estar dentro del rango (18-100)." << endl;
            verification = false;
        }

    }
    while (!verification || add.age < 18 || add.age > 100);

    getch();
    cout << endl;

    // Género
    cout << "Seleccione un género:" << endl;
    cout << "1. Masculino" << endl;
    cout << "2. Femenino" << endl;
    cout << "3. Otro" << endl;
    cin >> add.gender;

    cout << "Género seleccionado: ";
    switch (add.gender)
    {
    case 1:
        cout << "Masculino" << endl;
        break;
    case 2:
        cout << "Femenino" << endl;
        break;
    case 3:
        cout << "Otro" << endl;
        break;
    default:
        cout << "Opción inválida" << endl;
        break;
    }

    student.push_back(add);

    // Almacenar el archivo.

    ofstream archivo("ESTUDIANTES.txt", ios::app);
    if (archivo.is_open())
    {
        archivo << "Identificación:" << add.id  << "\n"
                << "Nombre completo:" << add.fullName << "\n"
                << "Provincia:" << add.province << "\n"
                << "Cantón:" << add.canton << "\n"
                << "Distrito:" << add.district << "\n"
                << "Edad:" << add.age<< "\n"
                << "Género:" <<add.gender << "\n";

        archivo.close();

        cout << "Estudiante registrado con éxito en 'ESTUDIANTES.txt'" << endl;
    }
    else
    {
        cout << "Error al abrir el archivo para guardar el estudiante." << endl;
    }
    getch();
    cout << endl;
}

// Función para las calificaciones.

// Verificar identificación del estudiante.

void IngresarCalificaciones(vector<Califications>& califications)
{
    string id;
    char respuesta;
    bool VoF = false;

    cout << "-------------------------------------------------------------------"<<endl;
    cout << "|                 REGISTRO DE NOTAS POR MATERIA                   |"<<endl;
    cout << "------------------------------------------------------------------ "<<endl;
    getch();
    cout << endl;

    do
    {
        cout << "Ingrese la identificación del estudiante (10 dígitos): ";
        cin >> id;
        cin.ignore();

        // Buscar en el archivo ESTUDIANTES.txt

        ifstream archivo("ESTUDIANTES.txt");
        string palabra;

        VoF = false;
        while (archivo >> palabra)
        {
            if (palabra == "Identificación:")
            {
                archivo >> palabra; // Leer la cédula
                if (palabra == id)
                {
                    VoF = true;

                    // Leer y mostrar el nombre
                    string etiqueta, nombre;
                    archivo >> etiqueta; // Lee "Nombre"
                    archivo >> etiqueta; // Lee "completo:"
                    getline(archivo, nombre); // El resto es el nombre
                    cout << "Nombre del estudiante:" << nombre << endl;
                    getch();
                    cout << endl;
                    break;
                }
            }
        }

        archivo.close();

        if (!VoF)
        {
            cout << " Estudiante no registrado";
            cout << "¿Desea ingresar otra identificación? (S/N): ";
            cin >> respuesta;
            respuesta = toupper(respuesta);
        }

    }
    while (!VoF && respuesta == 'S');

    if (!VoF)
    {
        cout << "Volver al menú principal"<< endl;
        getch();
        cout << endl;
        return;
    }


    // Registro de materias.

    int cantSubject;

    cout << "-------------------------------------------------------------------"<<endl;
    cout << "|                            MATERIA                              |"<< endl;
    cout << "-------------------------------------------------------------------"<<endl;
    getch();
    cout << endl;

    do
    {

        cout << "Ingrese la cantidad de tareas a registrar (máximo 3):";
        cin >> cantSubject;

        if (cantSubject < 1 || cantSubject > 3)
        {
            cout << "Error: debe ingresar mínimo una o como máximo tres tareas.";
        }

    }
    while(cantSubject < 1 || cantSubject > 3);
    getch();
    cout << endl;

    for (int i=0; i < cantSubject; i++)

    {

        Califications reg;
        reg.id = id;
        do
        {
            cout << "Ingrese el nombre de la materia:";
            cin.ignore();
            getline (cin,reg.subject);

            if (reg.subject.empty())
            {
                cout << "Error: no debe dejar el espacio vacío." << endl;
            }

        }
        while (reg.subject.empty());
        getch();
        cout << endl;

        // Calificaciones.

        float firstProject;
        float secondProject;
        float ensayo;
        float foro;
        float defense;

        do
        {
            cout << "Ingrese las notas en base 10:" << endl;
            getch();
            cout << endl;

            cout << "Proyecto 1:";
            cin >> reg.firstProject;

            if (reg.firstProject < 0 || reg.firstProject > 10 )
            {
                cout << "Vuelva a ingresar las notas" << endl;
            }
        }
        while (reg.firstProject < 0 || reg.firstProject > 10);

        do
        {

            cout << "Proyecto 2:";
            cin >> reg.secondProject;

            if (reg.secondProject < 0 || reg.secondProject > 10 )
            {
                cout << "Vuelva a ingresar la nota." << endl;
            }
        }
        while (reg.secondProject < 0 || reg.secondProject > 10);

        do
        {

            cout << "Ensayo:";
            cin >> reg.ensayo;

            if (reg.ensayo < 0 || reg.ensayo > 10 )
            {
                cout << "Vuelva a ingresar la nota." << endl;
            }
        }
        while (reg.ensayo < 0 || reg.ensayo > 10);

        do
        {

            cout << "Defensa:";
            cin >> reg.defense;

            if (reg.defense < 0 || reg.defense > 10 )
            {
                cout << "Vuelva a ingresar la nota." << endl;
            }
        }
        while (reg.defense < 0 || reg.defense > 10);

        do
        {

            cout << "Foro:";
            cin >> reg.foro;

            if (reg.foro < 0 || reg.foro > 10 )
            {
                cout << "Vuelva a ingresar la nota." << endl;
            }
        }
        while (reg.foro < 0 || reg.foro > 10);
        getch();
        cout << endl;

        // Calcular el promedio y su estado.

        float prom;

        prom= (reg.firstProject * 0.1 + reg.secondProject * 0.2 + reg.ensayo * 0.3 + reg.defense * 0.1+ reg.foro * 0.3);
        cout << "Promedio calculado:" << prom << endl;

        if (prom >= 70 && prom <= 100)
        {
            cout << "Estado: Aprobó" << endl;
        }
        else if (prom >= 50 && prom <= 69)
        {
            cout << "Estado: Reposición" << endl;
        }
        else if (prom < 50)
        {
            cout << "Estado: Reprobó" << endl;
        }
        getch();
        cout << endl;

        // Archivo.

        ofstream archivoNotas("CALIFICACIONES.txt", ios::app);

        if (archivoNotas.is_open())
        {
            archivoNotas << reg.id << endl;
            archivoNotas << reg.subject << endl;
            archivoNotas << reg.firstProject << endl;
            archivoNotas << reg.secondProject << endl;
            archivoNotas << reg.ensayo << endl;
            archivoNotas << reg.defense << endl;
            archivoNotas << reg.foro << endl;
            archivoNotas << prom << endl;
            archivoNotas << "Estado: " << (prom >= 7.0 ? "Aprobado" : "Reprobado") << endl;
            archivoNotas << "------------------------------------" << endl;

            archivoNotas.close();
        }
        else
        {
            cout << "Error al abrir el archivo para guardar las calificaciones." << endl;
        }

    }
}
void ModificarDatosEstudiante(vector<Student>& student)
{
    string id;
    char respuesta = 'S';
    bool hh = false;
    string newProvince;
    string newCanton;
    string newDistrict;

    cout << "-------------------------------------------------------------------"<<endl;
    cout << "|                       MODIFICAR ESTUDIANTE                       |"<< endl;
    cout << "-------------------------------------------------------------------"<<endl;
    getch();
    cout << endl;

    do
    {
        cout << "Digite la identificación de la persona (10 dígitos): ";
        cin >> id;
        cin.ignore();

        bool verificationID = true;
        if (id.length() != 10)
        {
            verificationID = false;
        }
        else
        {
            for (int i = 0; i < id.length(); i++)
            {
                if (id[i] < '0' || id[i] > '9')
                {
                    verificationID = false;
                    break;
                }
            }
        }

        if (!verificationID)
        {
            cout << "Error: la identificación debe tener 10 dígitos numéricos." << endl;
            getch();
            cout << endl;
            continue;
        }
        getch();
        cout << endl;

        // Modificar lugar de residencia.

        cout << "Ingrese la nueva provincia: ";
        getline(cin, newProvince);

        cout << "Ingrese el nuevo cantón: ";
        getline(cin, newCanton);

        cout << "Ingrese el nuevo distrito: ";
        getline(cin, newDistrict);

        // Modificar edad.

        int newAge;
        bool newAgeValida = false;
        do
        {
            cout << "Ingrese la nueva edad (18-100): ";
            cin >> newAge;
            if (cin.fail() || newAge < 18 || newAge > 100)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Nueva edad inválida. Intente de nuevo." << endl;
            }
            else
            {
                newAgeValida = true;
            }
        }
        while (!newAgeValida);
        cin.ignore();

        fstream archivo("ESTUDIANTES.txt", ios::in | ios::out);
        if (!archivo)
        {
            cerr << "Error al abrir el archivo" << endl;
            getch();
            cout << endl;
            return;
        }

        vector <Student>students;
        Student temp;
        bool registrado = false;

        while (archivo >> temp.id >> temp.fullName >> temp.province >> temp.canton >> temp.district >> temp.age >> temp.gender)
        {
            if (temp.id == id)
            {
                temp.province = newProvince;
                temp.canton = newCanton;
                temp.district = newDistrict;
                temp.age = newAge;
                registrado = true;
            }
            students.push_back(temp);
        }
        if (!registrado)
        {
            cout << "Estudiante no registrado." << endl;
            archivo.close();
            return;
        }

// Volver al inicio del archivo y truncarlo

        archivo.clear();
        archivo.seekp(0);


        for (const auto& est : students)
        {
            cout << est.id  << "\n";
            cout << est.fullName << "\n";
            cout << est.province << "\n";
            cout << est.canton << "\n";
            cout  << est.district << "\n";
            cout  << est.age<< "\n";
            cout << est.gender << "\n";

            cout << "==============================" << endl;


        }

        for (const auto& est : students)
        {
            archivo << est.id  << "\n"
                    << est.fullName << "\n"
                    << est.province << "\n"
                    << est.canton << "\n"
                    << est.district << "\n"
                    << est.age<< "\n"
                    << est.gender << "\n";
        }

        archivo.close();
        cout << "Datos actualizados correctamente" << endl;
        getch ();
        cout << endl;

    }
    while (!hh && respuesta == 'S');

    getch();
    cout << endl;
}

// Función case 4.

void ModificarRegistroEstudiante (vector<Califications>&califications)
{

    cout << "-------------------------------------------------------------------"<<endl;
    cout << "|                    MODIFICAR NOTAS ESTUDIANTE                    |"<< endl;
    cout << "-------------------------------------------------------------------"<<endl;

    char respuesta = 'S';
    bool hh = false;
    string id;
    string subject;
    float newFirstProject;
    float newSecondProject;
    float newEnsayo;
    float newForo;
    float newDefense;
    float newProm;

    do
    {

        cout << "Digite la identificación de la persona (10 dígitos): ";
        cin >> id;
        cin.ignore();

        bool verificationID = true;
        if (id.length() != 10)
        {
            verificationID = false;
        }
        else
        {
            for (int i = 0; i < id.length(); i++)
            {
                if (id[i] < '0' || id[i] > '9')
                {
                    verificationID = false;
                    break;
                }
            }
        }

        if (!verificationID)
        {
            cout << "Error: la identificación debe tener 10 dígitos numéricos." << endl;
            getch();
            cout << endl;
            continue;
        }
        getch();
        cout << endl;

        // Modificar las notas.

        cout << "Ingrese la nueva nota para el primer proyecto: ";
        cin >> newFirstProject;

        cout << "Ingrese la nueva nota para el segundo proyecto: ";
        cin >> newSecondProject;

        cout << "Ingrese la nueva nota para el ensayo: ";
        cin >> newEnsayo;

        cout << "Ingrese la nueva nota para el foro: ";
        cin >> newForo;

        cout << "Ingrese la nueva nota para la defensa: ";
        cin >> newDefense;

        // Promedio

        newProm= (newFirstProject * 0.1 + newSecondProject * 0.2 + newEnsayo * 0.3 + newDefense * 0.1+ newForo * 0.3);
        cout << "Nuevo promedio calculado:" << newProm << endl;

        if (newProm >= 70 && newProm <= 100)
        {
            cout << "Estado: Aprobó" << endl;
        }
        else if (newProm >= 50 && newProm <= 69)
        {
            cout << "Estado: Reposición" << endl;
        }
        else if (newProm < 50)
        {
            cout << "Estado: Reprobó" << endl;
        }
        getch();
        cout << endl;

        fstream archivoNotas("CALIFICACIONES.txt", ios::in | ios::out);
        if (!archivoNotas)
        {
            cerr << "Error al abrir el archivo" << endl;
            getch();
            cout << endl;
            return;
        }

        vector <Califications>califications;
        Califications temp;
        bool registrado = false;

        while (archivoNotas >> temp.id >> temp.subject >> temp.firstProject >> temp.secondProject >> temp.ensayo >> temp.foro >> temp.defense >> temp.prom)

        {
            if (temp.id == id && temp.subject == subject)
            {
                temp.firstProject = newFirstProject;
                temp.secondProject = newSecondProject;
                temp.ensayo = newEnsayo;
                temp.foro = newForo;
                temp.defense = newDefense;
                temp.prom = newProm;

                registrado = true;
            }
            califications.push_back(temp);
        }
        if (!registrado)
        {
            cout << "Estudiante no registrado." << endl;
            archivoNotas.close();
            return;
        }

        // Volver al inicio del archivo y truncarlo

        archivoNotas.clear();
        archivoNotas.seekp(0);


        for (const auto& est : califications)
        {
            cout << est.id  << "\n";
            cout << est.subject << "\n";
            cout << est.firstProject << "\n";
            cout << est.secondProject << "\n";
            cout << est.ensayo << "\n";
            cout  << est.foro << "\n";
            cout  << est.defense<< "\n";
            cout << est.prom << "\n";

            cout << "==============================" << endl;


        }

        for (const auto& est : califications)
        {
            archivoNotas << est.id  << "\n"
                         << est.subject << "\n"
                    << est.firstProject << "\n"
                    << est.secondProject << "\n"
                    << est.ensayo << "\n"
                    << est.foro << "\n"
                    << est.defense<< "\n"
                    << est.prom << "\n";
        }

        archivoNotas.close();
        cout << "Datos actualizados correctamente" << endl;
        getch ();
        cout << endl;

    }
    while (!hh && respuesta == 'S');

}

