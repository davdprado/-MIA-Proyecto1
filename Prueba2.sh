/*crearemos 8 discos...*/
/*verificar tamaño de discos...*/
MKdisk $SiZe=>120 $path=>"/tmp/archivos/fase 1/" $nAMe=>D1.dsk
/*Verificacion de mensaje de confirmacion de eliminacion de discos*/
RMdisk $patH=>"/tmp/archivos/fase 1/D1.dsk"
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