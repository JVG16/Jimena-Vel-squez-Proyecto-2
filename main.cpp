#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

int main()
{
    setlocale(LC_CTYPE,"Spanish"); //Idioma y car�cteres especiales.
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
        cout << "Digite por favor un n�mero del 1-7" << endl;
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

            // Indentificaci�n.

            string identification;
            bool verification;
            do
            {
                verification = true;
                cout << "Ingrese la identificaci�n del estudiante (10 d�gitos):";
                cin >> identification;
                if (identification.length() != 10)
                {
                    verification = false;
                }
                else
                {
                    for (int i = 0; i < identification.length(); i++)
                    {
                        if (identification[i] < '0' || identification[i] > '9')
                        {
                            verification = false;
                            break;
                        }
                    }

                    bool todosIguales = true;
                    for (int i = 1; i < identification.length(); i++)
                    {
                        if (identification[i] != identification[0])
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
                    cout << "Error: debe ingresar 10 n�meros y que no se repitan." << endl;
                }
            }
            while (!verification);

            cin.ignore();

            // Nombre completo.

            string completeName;

            do
            {
                verification = true;
                cout << "Ingrese el nombre completo (nombre y apellidos):";
                getline (cin,completeName);

                for (int i = 0; i < completeName.length(); i++)
                {
                    if (!((completeName[i] >= 'A' && completeName[i] <= 'Z') ||(completeName[i] >= 'a' && completeName[i] <= 'z') || completeName[i] == ' '))
                    {
                        verification = false;
                        break;
                    }
                }

                if (!verification || completeName.length() == 0)
                {
                    cout << "Error: solo debe ingresar letras y espacios." << endl;
                }

            }
            while (!verification || completeName.length() == 0);

            // Residencia.
            string province;
            string canton;
            string distrite;

            cout << "Ingrese el lugar de residencia" << endl;
            cout << "- Provincia:";
            getline(cin,province);

            cout << "- Cant�n:";
            getline(cin,canton);

            cout << "- Distrito:";
            getline(cin,distrite);

            // Edad.

            int age;
            do
            {
                verification = true;
                cout << "Ingrese la edad (18-100):";
                cin >> age;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Error: debe ingresar un n�mero v�lido." << endl;
                    verification = false;
                }

                if(age < 18 || age > 100)
                {
                    cout << "Error: la edad debe estar dentro del rango (18-100). Vuelva a intentarlo." << endl;
                    verification = false;
                }

            }
            while(age < 18 || age > 100);

            // G�nero.

            int select;

            cout << "Seleccione un g�nero:" << endl;
            cout << "1. Masculino:" << endl;
            cout << "2. Femenino:" << endl;
            cout << "3. Otro:" << endl;
            cin >> select;

            cout << "G�nero seleccionado: "<< endl;

            switch (select)
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
                cout << "Opci�n inv�lida" << endl;
                break;
            }

            cout << "Estudiante registrado con �xito en " "ESTUDIANTES.txt" << endl;

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
                cout << "Opci�n no v�lida" << endl;
            }

        }
    }
    while(option != 7);
    return 0;
}
