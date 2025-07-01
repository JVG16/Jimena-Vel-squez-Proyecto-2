#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
    setlocale(LC_CTYPE,"Spanish"); //Idioma y carácteres especiales.
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
            cout << "Registrar estudiante."<< endl;
            getch();
            cout << endl;
            break;
        }
        case 2:
        {
            cout << "Ingresar calificaciones en distintas materias." << endl;
            getch();
            cout << endl;
            break;
        }
        case 3:
        {
            cout << "Modificar datos estudiantes." << endl;
            getch();
            cout << endl;
            break;
        }
        case 4:
        {
            cout << "Modificar registo de notas por estudiante." << endl;
            getch();
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
