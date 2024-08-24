
# Manual de Usuario - Sistema de Gestión de Redes Sociales - 202103763

## Índice
1. [Iniciar Sesión](#iniciar-sesión)
2. [Registrarse](#registrarse)
3. [Información](#información)
4. [Salir](#salir)
5. [Carga de Usuarios](#carga-de-usuarios)
6. [Carga de Solicitudes](#carga-de-solicitudes)
7. [Carga de Publicaciones](#carga-de-publicaciones)
8. [Gestión de Usuarios](#gestión-de-usuarios)
9. [Reportes](#reportes)
10. [Cerrar Sesión](#cerrar-sesión)

---

## Iniciar Sesión

Para iniciar sesión en el sistema:

1. Selecciona la opción `1` del menú principal.
2. Ingresa tu correo electrónico.
3. Ingresa tu contraseña.
4. Si eres administrador, verás el mensaje:
   ```
   Bienvenido Administrador
   ```
5. Se desplegará el siguiente menú de opciones:

   ```
   1. Carga de usuarios
   2. Carga de solicitudes
   3. Carga de publicaciones
   4. Gestion de usuarios
   5. Reportes
   6. Cerrar sesión
   ```

## Registrarse

Esta funcionalidad aún no está implementada.

## Información

Esta funcionalidad aún no está implementada.

## Salir

Para salir del sistema:

1. Selecciona la opción `4` en el menú principal.

## Carga de Usuarios

Para cargar usuarios desde un archivo JSON:

1. Selecciona la opción `1` en el menú de administración.
2. Ingresa la ruta del archivo JSON con los datos de los usuarios.
3. El sistema mostrará un mensaje de éxito para cada usuario registrado:
   ```
   Nombre registrado exitosamente.
   ```

## Carga de Solicitudes

Para cargar solicitudes de amistad desde un archivo JSON:

1. Selecciona la opción `2` en el menú de administración.
2. Ingresa la ruta del archivo JSON con los datos de las solicitudes.
3. El sistema mostrará un mensaje de confirmación para cada solicitud cargada, indicando su estado (`ACEPTADA` o `PENDIENTE`):
   ```
   La solicitud de [emisor] a [receptor] ha sido añadida con estado: [estado]
   ```

## Carga de Publicaciones

Para cargar publicaciones desde un archivo JSON:

1. Selecciona la opción `3` en el menú de administración.
2. Ingresa la ruta del archivo JSON con los datos de las publicaciones.
3. El sistema confirmará la finalización del proceso:
   ```
   Proceso de carga desde [ruta] finalizado.
   ```

## Gestión de Usuarios

Para gestionar usuarios:

1. Selecciona la opción `4` en el menú de administración.
2. Se presentará el siguiente submenú:

   ```
   a. Eliminar usuarios
   x. volver
   ```

3. Para eliminar un usuario:
   - Ingresa `a`.
   - El sistema mostrará la lista de usuarios con su ID, nombre, correo y contraseña.
   - Ingresa el correo electrónico del usuario a eliminar.
   - El sistema confirmará la eliminación del usuario:
     ```
     Se ha eliminado al usuario [correo]
     ```

4. Para volver al menú anterior, ingresa `x`.

## Reportes

Para generar reportes:

1. Selecciona la opción `5` en el menú de administración.
2. El sistema mostrará un reporte con el "Top 5 correos con más publicaciones":
   ```
   1. [correo] - [número] publicaciones
   2. [correo] - [número] publicaciones
   ...
   ```

## Cerrar Sesión

Para cerrar sesión:

1. Selecciona la opción `6` en el menú de administración.
2. El sistema mostrará el mensaje:
   ```
   Ha cerrado sesión
   ```

---

# Social Structure

1. **Iniciar sesión**
2. **Registrarse**
3. **Información**
4. **Salir**

Ingrese una opción: `1`

## Iniciar sesión
Ingrese su correo electrónico: `juan.martinez@example.com`
Ingrese su contraseña: `Mn64@trX`

---

**Juan Martinez [Activo]**

1. **Perfil**
2. **Solicitudes**
3. **Publicaciones**
4. **Reportes**
5. **Cerrar sesión**

Ingrese una opción: `1`

### Perfil

a. **Ver perfil**  
b. **Eliminar cuenta**  
x. **Volver**

Ingrese una opción (a) Ver perfil (b) Eliminar cuenta (x) Volver: `a`

**Juan Martinez [Estado: Activo]**  
Correo: `juan.martinez@example.com`  
Fecha de nacimiento: `1992/02/17`  
Amigos en [Social Structure]

- `ana.hernandez@example.com`

a. **Ver perfil**  
b. **Eliminar cuenta**  
x. **Volver**

Ingrese una opción (a) Ver perfil (b) Eliminar cuenta (x) Volver: `x`

Saliendo de perfil...

**Juan Martinez [Activo]**

1. **Perfil**
2. **Solicitudes**
3. **Publicaciones**
4. **Reportes**
5. **Cerrar sesión**

Ingrese una opción: `2`

### Solicitudes

a. **Ver solicitudes**  
b. **Enviar solicitud**  
x. **Volver**

Ingrese una opción (a) Ver solicitudes (b) Enviar solicitud (x) Volver: `a`

#### Solicitudes recibidas en estado [PENDIENTE]

- `jose.garcia@example.com`
- `miguel.rodriguez@example.com`
- `laura.ramirez@example.com`

i. **Elegir usuario a Aceptar/Rechazar**  
x. **Volver**

Ingrese una opción (i para elegir a una solicitud a aceptar/rechazar, x para volver): `i`

Ingrese el correo del usuario a Aceptar/Rechazar: `laura.ramirez@example.com`

a. **Aceptar**  
b. **Rechazar**  
x. **Volver**

Ingrese una opción (a) Aceptar (b) Rechazar (x) Volver): `a`

Se ha **ACEPTADO** la solicitud de `laura.ramirez@example.com`

#### Solicitudes recibidas en estado [PENDIENTE]

- `jose.garcia@example.com`
- `miguel.rodriguez@example.com`

i. **Elegir usuario a Aceptar/Rechazar**  
x. **Volver**

Ingrese una opción (i para elegir a una solicitud a aceptar/rechazar, x para volver): `i`

Ingrese el correo del usuario a Aceptar/Rechazar: `jose.garcia@example.com`

a. **Aceptar**  
b. **Rechazar**  
x. **Volver**

Ingrese una opción (a) Aceptar (b) Rechazar (x) Volver): `b`

Se ha **RECHAZADO** la solicitud de `jose.garcia@example.com`

#### Solicitudes recibidas en estado [PENDIENTE]

- `miguel.rodriguez@example.com`

i. **Elegir usuario a Aceptar/Rechazar**  
x. **Volver**

Ingrese una opción (i para elegir a una solicitud a aceptar/rechazar, x para volver): `x`

Saliendo de vista de **solicitudes**  
a. **Ver solicitudes**  
b. **Enviar solicitud**  
x. **Volver**

Ingrese una opción (a) Ver solicitudes (b) Enviar solicitud (x) Volver: `x`

Saliendo de solicitudes...

**Juan Martinez [Activo]**

1. **Perfil**
2. **Solicitudes**
3. **Publicaciones**
4. **Reportes**
5. **Cerrar sesión**

Ingrese una opción: `1`

### Perfil

a. **Ver perfil**  
b. **Eliminar cuenta**  
x. **Volver**

Ingrese una opción (a) Ver perfil (b) Eliminar cuenta (x) Volver: `a`

**Juan Martinez [Estado: Activo]**  
Correo: `juan.martinez@example.com`  
Fecha de nacimiento: `1992/02/17`  
Amigos en [Social Structure]

- `ana.hernandez@example.com`
- `laura.ramirez@example.com`

a. **Ver perfil**  
b. **Eliminar cuenta**  
x. **Volver**

Ingrese una opción (a) Ver perfil (b) Eliminar cuenta (x) Volver: `x`

Saliendo de perfil...

**Juan Martinez [Activo]**

1. **Perfil**
2. **Solicitudes**
3. **Publicaciones**
4. **Reportes**
5. **Cerrar sesión**

Ingrese una opción: `3`

### Publicaciones

a. **Ver publicaciones**  
b. **Crear publicación**  
c. **Eliminar publicación**  
x. **Volver**

Ingrese una opción (a) Ver publicaciones (b) Crear publicación (c) Eliminar publicación (x) Volver): `a`

#### Ver publicaciones de Juan Martinez

- **[Autor]** `juan.martinez@example.com`  
  **[Contenido]** El café de la mañana nunca decepciona, ¡energía pura para el día!  
  **[Fecha]** 10/08/2024  
  **[Hora]** 07:30

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `s`

- **[Autor]** `juan.martinez@example.com`  
  **[Contenido]** A veces solo necesitas una taza de té y un buen libro.  
  **[Fecha]** 21/08/2024  
  **[Hora]** 20:30

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `s`

- **[Autor]** `ana.hernandez@example.com`  
  **[Contenido]** Los atardeceres en la ciudad son simplemente mágicos, me encanta.  
  **[Fecha]** 13/08/2024  
  **[Hora]** 18:12

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `s`

- **[Autor]** `ana.hernandez@example.com`  
  **[Contenido]** Recordando viejos tiempos con amigos, esas memorias nunca se olvidan.  
  **[Fecha]** 12/08/2024  
  **[Hora]** 21:05

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `s`

- **[Autor]** `laura.ramirez@example.com`  
  **[Contenido]** La lectura de un buen libro puede cambiar tu perspectiva del mundo.  
  **[Fecha]** 20/08/2024  
  **[Hora]** 16:45

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `a`

- **[Autor]** `ana.hernandez@example.com`  
  **[Contenido]** Recordando viejos tiempos con amigos, esas memorias nunca se olvidan.  
  **[Fecha]** 12/08/2024  
  **[Hora]** 21:05

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `a`

- **[Autor]** `ana.hernandez@example.com`  
  **[Contenido]** Los atardeceres en la ciudad son simplemente mágicos, me encanta.  
  **[Fecha]** 13/08/2024  
  **[Hora]** 18:12

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `q`

a. **Ver publicaciones**  
b. **Crear publicación**  
c. **Eliminar publicación**  
x. **Volver**

Ingrese una opción (a) Ver publicaciones (b) Crear publicación (c) Eliminar publicación (x) Volver): `b`

### Crear publicación

Ingrese el contenido de la publicación: `nueva publicación realizada`

a. **Ver publicaciones**  
b. **Crear publicación**  
c. **Eliminar publicación**  
x. **Volver**

Ingrese una opción (a) Ver publicaciones (b) Crear publicación (c) Eliminar publicación (x) Volver): `a`

#### Ver publicaciones de Juan Martinez

- **[Autor]** `juan.martinez@example.com`  
  **[Contenido]** El café de la mañana nunca decepciona, ¡energía pura para el día!  
  **[Fecha]** 10/08/2024  
  **[Hora]** 07:30

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `a`

- **[Autor]** `laura.ramirez@example.com`  
  **[Contenido]** La naturaleza siempre tiene una forma de sorprendernos, es increíble.  
  **[Fecha]** 20/08/2024  
  **[Hora]** 18:30

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `s`

- **[Autor]** `juan.martinez@example.com`  
  **[Contenido]** A veces solo necesitas una taza de té y un buen libro.  
  **[Fecha]** 21/08/2024  
  **[Hora]** 20:30

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `s`

- **[Autor]** `ana.hernandez@example.com`  
  **[Contenido]** Los atardeceres en la ciudad son simplemente mágicos, me encanta.  
  **[Fecha]** 13/08/2024  
  **[Hora]** 18:12

  -----------------------------------------------------

Opciones: (A)nterior | (S)iguiente | (Q)uitar: `q`

a. **Ver publicaciones**  
b. **Crear publicación**  
c. **Eliminar publicación**  
x. **Volver**

Ingrese una opción (a) Ver publicaciones (b) Crear publicación (c) Eliminar publicación (x) Volver): `x`

Saliendo de publicaciones...

**Juan Martinez [Activo]**

1. **Perfil**
2. **Solicitudes**
3. **Publicaciones**
4. **Reportes**
5. **Cerrar sesión**

Ingrese una opción: `5`

### Cerrar sesión

Saliendo del sistema...



# Social Structure

1. **Iniciar sesión**
2. **Registrarse**
3. **Información**
4. **Salir**

Ingrese una opción: `2`

## Registro

Ingrese su nombre: `lourdes`  
Ingrese su apellido: `manuel`  
Ingrese su fecha de nacimiento (DD/MM/AAAA): `30/01/2001`  
Ingrese su correo electrónico: `si@gmail`  
Ingrese su contraseña: `si`  

**lourdes manuel registrado exitosamente.**

# Social Structure [login]

1. **Iniciar sesión**
2. **Registrarse**
3. **Información**
4. **Salir**

Ingrese una opción: `1`

## Iniciar sesión

Ingrese su correo electrónico: `si@gmail`  
Ingrese su contraseña: `si`

**lourdes manuel [Activo]**

1. **Perfil**
2. **Solicitudes**
3. **Publicaciones**
4. **Reportes**
5. **Cerrar sesión**

Ingrese una opción:

