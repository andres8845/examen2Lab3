#ifndef USUARIO_H
#define USUARIO_H
#include <QStringListModel>
#include <QString>

struct Usuario {
    QString nombre;
    QString usuario;
    QString contraseña;
    QString fecha;
};

class UsuarioManager {
public:
    static bool crearUsuario(const Usuario& nuevoUsuario);

    static bool login(const QString& usuario, const QString& contraseña);
};

#endif // USUARIO_H
