export interface FicheroI{
    id: number;
    Nombre: string;
    FechaC:string;
    Contenido:FicheroI[];
};

export interface CorreoI{
    correo:string;
};