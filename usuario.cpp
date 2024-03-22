
#include "usuario.h"
#include <QFile>
#include <QDataStream>
#include <QStringListModel>

bool UsuarioManager::crearUsuario(const Usuario& nuevoUsuario) {

    QFile file("usuariosfile.us");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Append)) {
        return false;
    }

    QDataStream in(&file);
    file.seek(0);
    Usuario usuarioExistente;
    while (!in.atEnd()) {
        in >> usuarioExistente.nombre >> usuarioExistente.usuario >> usuarioExistente.contraseña >> usuarioExistente.fecha;
        if (usuarioExistente.usuario == nuevoUsuario.usuario) {
            file.close();
            return false;
        }
    }


    QDataStream out(&file);
    out << nuevoUsuario.nombre << nuevoUsuario.usuario << nuevoUsuario.contraseña << nuevoUsuario.fecha;

    file.close();
    return true;
}


bool UsuarioManager::login(const QString& usuario, const QString& contraseña) {
    QFile file("usuariosfile.us");
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QDataStream in(&file);
    Usuario usuarioRegistrado;
    file.seek(0);
    while (!in.atEnd()) {
        in >> usuarioRegistrado.nombre >> usuarioRegistrado.usuario >> usuarioRegistrado.contraseña >> usuarioRegistrado.fecha;
        if (usuarioRegistrado.usuario == usuario && usuarioRegistrado.contraseña == contraseña) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
