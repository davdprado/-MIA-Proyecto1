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
/*nAMe:	PRI1		PRI2		EXT			LOG1	LOG2	LOG3	LOG4	LOG5	LOG6	LOG7	LOG8   PRI3*/
fdisk $SiZe=>10 @UniT=>M $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>P @fit=>FF $nAMe=>PRI1
fdisk $path=>"/tmp/archivos/fase 1/D1.dsk" $SiZe=>5120 @fit=>BF $nAMe=>PRI2
fdisk $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>E $nAMe=>"EXT" $SiZe=>51200
fdisk @type=>L $SiZe=>5120 @Unit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG1
fdisK $nAMe=>LOG2 $SiZe=>5120 $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>L
fdisk @type=>L $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG3 $SiZe=>5120 @uniT=>K
fdiSk @type=>L $SiZe=>5120 @unIt=>K $PAth=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG4
fdisk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG5
FdisK $SiZe=>5120 $nAMe=>LOG6 @UNit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>L
fdIsk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG7
fdIsk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG8 @fit=>BF
fdisk @unit=>B $path=>"/tmp/archivos/fase 1/D1.dsk" $SiZe=>5242880 $nAMe=>PRI3

/*Crearemos las mismas 12 particiones en el tercer disco*/
/*PrimarIA 1 es de 10 Mb*/
/*eL RESTO son de 5 Mb (La extendida es de 50 Mb)*/
/*Tipo:		Primaria	Primaria	Extendida	Logica	Logica	Logica	Logica	Logica	Logica	Logica	Logica Primaria*/
/*Ajuste:	Primer 		Mejor		$			Peor	Peor	Peor	Peor	Peor	Peor	Peor	Mejor   Peor*/
/*nAMe:	PRI1		PRI2		EXT			LOG1	LOG2	LOG3	LOG4	LOG5	LOG6	LOG7	LOG8   PRI3*/

fdisk $SiZe=>10 @UniT=>M $path=>"/tmp/archivos/fase 1/D3.dsk"     @type=>P @fit=>FF $nAMe=>PRI1
fdisk $path=>"/tmp/archivos/fase 1/D3.dsk" $SiZe=>5120 	 @fit=>BF $nAMe=>PRI2
FdisK $path=>"/tmp/archivos/fase 1/D3.dsk" @type=>E $nAMe=>EXT $SiZe=>51200
fdisk @type=>L $SiZe=>5120 @Unit=>K $path=>"/tmp/archivos/fase 1/D3.dsk" $nAMe=>LOG1
fdisK $nAMe=>LOG2 $SiZe=>5120 $path=>"/tmp/archivos/fase 1/D3.dsk" @type=>L
fdisk @type=>L $path=>"/tmp/archivos/fase 1/D3.dsk" $nAMe=>LOG3 $SiZe=>5120 @uniT=>K
fdiSk $SiZe=>5120 @unIt=>K $PAth=>"/tmp/archivos/fase 1/D3.dsk" $nAMe=>LOG4 @type=>L
fdisk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D3.dsk" $nAMe=>LOG5
FdisK $SiZe=>5120 $nAMe=>LOG6 @UNit=>K $path=>"/tmp/archivos/fase 1/D3.dsk" @type=>L
fdIsk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D3.dsk" $nAMe=>LOG7
fdIsk @type=>L $SiZe=>5120 @unit=>K $path=>"/tmp/archivos/fase 1/D3.dsk" $nAMe=>LOG8 @fit=>BF
fdisk @unit=>B $path=>"/tmp/archivos/fase 1/D3.dsk" $SiZe=>5242880 $nAMe=>PRI3

/*Verificar generacion de ids al montar*/
/*Debería generar los ids: vda1, vdb1, vda2, vdb2*/
/*vda para el d3.dsk y vdb para d1.dsk*/
mouNt $nAMe=>PRI3 $path=>"/tmp/archivos/fase 1/D3.dsk"
pause
moUnt $PAth=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI3
mOunt $nAMe=>PRI2 $path=>"/tmp/archivos/fase 1/D3.dsk"
mouNt $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI2
pause

/*Validaciones al montar, no deberia cargarlos*/
moUnt $nAMe=>PX $path=>"/tmp/archivos/fase 1/D3.dsk"
moUNt $path=>"/tmp/archivos/fase 1/DX.dsk" $nAMe=>PRI3
pause
/*Listar las particiones montadas*/
/*mouNt
/*SAlida es la siguiente*/
/*id=>vda1 $path=>"/tmp/archivos/fase 1/D3.dsk" $nAMe=>PRI3*/
/*id=>vdb1 $PAth=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI3*/
/*id=>vda2 $path=>"/tmp/archivos/fase 1/D3.dsk" $nAMe=>PRI2*/
/*id=>vdb2 $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI2*/

/*Reporte de las particiones del disco*/
/*Debe crear la carpeta de reportes*/
rep $nAMe=>disk $path=>"/tmp/archivos/fase 1/reportes/Reporte1_Disco_Disco3.jpg" $id=>vda1
rep $path=>"/tmp/archivos/fase 1/reportes/Reporte1_disco_Disco1.jpg" $id=>vdb1 $nAMe=>disk
rep $nAMe=>mbr $path=>"/tmp/archivos/fase 1/reportes/Reporte1_MBR_Disco3.jpg" $id=>vda1
rep $path=>"/tmp/archivos/fase 1/reportes/Reporte1_MBR_Disco1.jpg" $id=>vdb1 $nAMe=>mbr
pause
/*Vericamos la eliminación*/
/*Elimina la primaria 2, logica 1, logica 2 y logica 5 del disco 1*/
/*Queda así: P1 EXT L2 L3 L6 L7 L8 P3*/
fdisk @delete=>Fast $nAMe=>PRI2 $path=>"/tmp/archivos/fase 1/D1.dsk"
fdisk $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG1 @delete=>FasT
fDisk $nAMe=>LOG4 @delete=>FaST $PAth=>"/tmp/archivos/fase 1/D1.dsk"
fdisK $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG5 @delete=>FAsT

/*Tambien elimina la partición extendida y la primaria 1 del disco 3*/
/*Verificar que no queden EBRs*/
/*Queda así: P2 P3*/
fDisk $DELete=>Full $nAMe=>EXT $path=>"/tmp/archivos/fase 1/D3.dsk" @Delete=>Full
fdisk @Delete=>Full $nAMe=>PRI1 @Delete=>Full $path=>"/tmp/archivos/fase 1/D3.dsk"

/*Reporte con particiones eliminadas*/
rep $id=>vda1 $nAMe=>disk $path=>"/tmp/archivos/fase 1/reportes/Reporte2_disco_Disco3.jpg"
rep $path=>"/tmp/archivos/fase 1/reportes/Reporte2_disco_Disco1.jpg" $nAMe=>disk $id=>vdb1
rep $nAMe=>mbr $path=>"/tmp/archivos/fase 1/reportes/Reporte2_MBR_Disco3.jpg" $id=>vda1
rep $path=>"/tmp/archivos/fase 1/reportes/Reporte2_MBR_Disco1.jpg" $id=>vdb1 $nAMe=>mbr

/*TEORIA DE PARTICIONES, (solo una extendida) debería dar error*/
fdisk $SiZe=>2048 $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>E $nAMe=>EXT2

/*Verificar PRIMER AJUSTE creando de nuevo las particiones*/
/*Debe quedar de la siguiente forma:*/
/*Disco1: PRIMARIA1 PRIMARIA2 EXTENDIDA LOGICA1 LOGICA2 LOGICA3 LOGICA45 LOGICA6 LOGICA7 LOGICA8 PRIMARIA3*/
fdiSk @unit=>M $SiZe=>5 $path=>"/tmp/archivos/fase 1/D1.dsk" @type=>P @fit=>FF $nAMe=>PRI2
fdisk $path=>"/tmp/archivos/fase 1/D1.dsk" $SiZe=>10240 @type=>L $nAMe=>LOG45 @unit=>K
fdisk $path=>"/tmp/archivos/fase 1/D1.dsk" $SiZe=>5120 @type=>L $nAMe=>LOG1 @unit=>K


/*Disco 3: Primaria2 EXTENDIDA LOGICA1 PRIMARIA1 PRIMARIA3*/
fdisk @type=>E $path=>"/tmp/archivos/fase 1/D3.dsk" $SiZe=>10240 $nAMe=>EXT
fdiSk $nAMe=>LOG1 @unit=>K $path=>"/tmp/archivos/fase 1/D3.dsk" @type=>L $SiZe=>5120
fdisk $SiZe=>10240 $nAMe=>PRI1 $path=>"/tmp/archivos/fase 1/D3.dsk" @type=>P

/*Reporte de las particiones del disco*/
Rep $Path=>"/tmp/archivos/fase 1/reportes/Reporte3_disco_Disco3.jpg" $id=>vda1 $nAMe=>disk
rep $nAMe=>disk $path=>"/tmp/archivos/fase 1/reportes/Reporte3_disco_Disco2.jpg" $id=>vdb1

/*Validaciones al crear o quitar espacio*/
/*No deberia ejecutar estas instrucciones*/
/*(porque no hay espacio después)*/
/*fdisk $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI1 @add=>3
/*(porque no debe quedar espacio negativo) debe mostrar mensaje de cuanto puede quitarle*/
/*fdisk @add=>-20 @unit=>M $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI1 @unit=>M
/*(Porque no hay suficiente espacio)*/
/*fdisk @unit=>M $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG7 @add=>150

/*Quita y agrega 1 mb de la primer particion*/
/*fdisk @unit=>M $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI1 @add=>-1
rep $nAMe=>Mbr $path=>"/tmp/archivos/fase 1/reportes/Reporte4_MBR_Espacio_Disco1.jpg" $id=>vdb2
/*fdisk @unit=>M $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI1 @add=>1
/*rep $nAMe=>Mbr $path=>"/tmp/archivos/fase 1/reportes/Reporte5_MBR_Espacio_Disco1.jpg" $id=>vdb2
/*Le quita 1 mb a la partición logica*/
/*fdisk @unit=>M $path=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>LOG45 @add=>1
/*rep $nAMe=>Mbr $path=>"/tmp/archivos/fase 1/reportes/Reporte6_Espacio_MBR Disco1.jpg" $id=>vdb2

/*desmontar una lista de ids
umount $id1=>vda1 $id2=>vdb2 $id=>vda2
/*para corroborar que desmonto hacer un mount para listar las particiones montadas*/
mount
/*Salida es la siguiente*/
/*id=>vdb1 $PAth=>"/tmp/archivos/fase 1/D1.dsk" $nAMe=>PRI3*/