export interface UsuarioI{
    id:number;
    nombre:string;
    apellido:string;
    telefono:string;
    username:string;
    fecha_nacimiento:string;
    correo:string;
    password:string;
    status:number;
    rol:string;
    fecha_registro:string;
};
export interface UsuarioCreate{
    nombre:string;
    apellido:string;
    username:string;
    correo:string;
    password:string;
    telefono:string;
    nacimiento:string;
};

export interface ResponseCUI{
    status: string;
    message:string;
};