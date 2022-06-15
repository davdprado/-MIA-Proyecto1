/*crearemos 8 discos...*/
/*verificar tamaño de discos...*/
MKdisk $SiZe=>120 $path=>"/tmp/archivos/fase 1/" $nAMe=>D1.dsk
mkdisK $SiZe=>32 $path=>"/tmp/archivos/fase 1/" $nAMe=>D2.dsk 
MKdisk $SiZe=>64 $PatH=>"/tmp/archivos/fase 1/" $nAMe=>D3.dsk
MKdisk $SiZe=>80 $path=>"/tmp/archivos/fase 1/" $nAMe=>D4.dsk 
MKdisk $SiZe=>120 $path=>"/tmp/archivos/fase 1/" $nAMe=>D5.dsk
MKdisk $SiZe=>8 $path=>"/tmp/archivos/fase 1/" $nAMe=>D6.dsk

/*vamos a verificar si hicieron validaciones con datos incorrectos*/
/*primero el SiZe tiene numero menor a 0, segundo el 60 no es multiplo de 8*/
MKdisk $SiZe=>-60 $path=>"/tmp/archivos/fase 1/" $nAMe=>D7.dsk
MKdisk $SiZe=>60 $path=>"/tmp/archivos/fase 1/" $nAMe=>D8.dsk

/*Eliminar discos, solo quedaran 3 discos*/
/*Verificacion de mensaje de confirmacion de eliminacion de discos*/
RMdisk $patH=>"/tmp/archivos/fase 1/D5.dsk"
RMdisk $patH=>"/tmp/archivos/fase 1/D4.dsk"

/*Verificando validaciones con datos incorrectos en el rmdisk*/
/*Deberia de dar error ya que el disco 8 no existe*/
rmDiSK $path=>"/tmp/archivos/fase 1/D8.dsk"

/*Crear 12 particiones del mismo tamaño en el primer disco con ajustes diferentes*/
/*PrimarIA 1 es de 10 Mb*/
/*Todas son de 5 Mb (La extendida es de 50 Mb)*/
/*Tipo:		Primaria	Primaria	Extendida	Logica	Logica	Logica	Logica	Logica	Logica	Logica	Logica Primaria*/
/*Ajuste:	Primer 		Mejor		$			Peor	Peor	Peor	Peor	Peor	Peor	Peor	Mejor   Peor*/
/*nAMe:	PRI 1		PRI 2		EXT			LOG 1	LOG 2	LOG 3	LOG 4	LOG 5	LOG 6	LOG 7	LOG8   PRI 3*/
fdisk $SiZe=>10 @UniT=>M $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>P @fit=>FF $nAMe=>PRI1
fdisk $path=>"/tmp/archivos/fase 1/D1.dsk" $SiZe=>5120 @fit=>BF $nAMe=>PRI2
fdisk $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>E $nAMe=>"EXT" $SiZe=>51200
fdisk @type=>L $SiZe=>5120 @Unit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG1
fdisK $nAMe=>LOG2 $SiZe=>5120 $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>L
fdisk @type=>L $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>"LOG 3" $SiZe=>5120 @uniT=>K
fdiSk @type=>L $SiZe=>5120 @unIt=>K $PAth=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG4
fdisk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG5
FdisK $SiZe=>5120 $nAMe=>LOG6 @UNit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>L
fdIsk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG7
fdIsk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG8 @fit=>BF
fdisk @unit=>B $path=>"/tmp/archivos/fase 1/D1.dsk" $SiZe=>5242880 $nAMe=>PRI3

/*Crearemos las mismas 12 particiones en el tercer disco*/
