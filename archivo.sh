# Archivo de Ejemplo 2
# MIA 1er Semestre 2022

# Creacion de primer disco
mkdisk -size=50 -unit=m -path=/tmp/mia/Disco1.dk

# Creacion particiones disco 1, 4 primarias
fdisk -Size=5 -path=/tmp/mia/Disco1.dk -unit=m -name=Particion1 -fit=ff
fdisk -S=1024 -path=/tmp/mia/Disco1.dk -unit=k -name=Particion2
#error debe ser size no s
fdisk -Size=1024 -path=/tmp/mia/Disco1.dk -unit=k -name=Particion2
fdisk -Size=10 -unit=m -path=/tmp/mia/Disco1.dk -name=Particion3
fdisk -Size=25 -path=/tmp/mia/Disco1.dk -name=Particion4 -fit=wf -unit=m
fdisk -Size=25 -path=/tmp/mia/Disco1.dk -name=Particion4 -fit=wf -unit=m
#error ya existe la parcion
pause
# Creacion de segundo y tercer disco
mkdisk -size=25 -fit=bf -unit=m -path=/tmp/mia/primersemestre/Disco2.dk
mkdisk -unit=m -size=75 -path=/tmp/mia/primersemestre/entrada1/Disco3.dk

# Creacion de particiones disco 2, 3 primarias 1 extendida
fdisk -Size=500 -unit=k -path=/tmp/mia/primersemestre/Disco2.dk -name=Particion1 -fit=ff
fdisk -Size=1024 -path=/tmp/mia/primersemestre/Disco2.dk -unit=k -name=Particion2
fdisk -Size=10 -unit=m -path=/tmp/mia/primersemestre/Disco2.dk -name=Particion3
fdisk -unit=k -Size=4096 -path=/tmp/mia/primersemestre/Disco2.dk -type=E -name=Particion4 -fit=wf

pause

# Creacion de particiones disco 3, 2 primarias, 1 extendida y 2 logicas
fdisk -Size=5000 -path=/tmp/mia/primersemestre/entrada1/Disco3.dk -name=Particion1 -unit=b
fdisk -Size=30 -path=/tmp/mia/primersemestre/entrada1/Disco3.dk -unit=m -type=E -fit=bf -name=Particion2
fdisk -Size=5 -type=L -unit=m -path=/tmp/mia/primersemestre/entrada1/Disco3.dk -name=Particion3
fdisk -type=L -unit=k -Size=4096 -path=/tmp/mia/primersemestre/entrada1/Disco3.dk -name=Particion4
fdisk -Size=3 -path=/tmp/mia/primersemestre/entrada1/Disco3.dk -name=Particion5 -unit=m

#editar particiones
fdisk -add=-3 -unit=m -name=Particion1 -path=/tmp/mia/Disco1.dk
fdisk -add=5 -unit=m -name=Particion3 -path=/tmp/mia/Disco1.dk

# montar
#201a
mount -path=/tmp/mia/Disco1.dk -name=Particion1
#202a
mount -path=/tmp/mia/primersemestre/Disco2.dk -name=Particion2
#203a
mount -path=/tmp/mia/primersemestre/entrada1/Disco3.dk -name=Particion3

#reporte
rep -id=201a -Path=/tmp/mia/reportes/mbr1.jpg -name=mbr
rep -id=201a -Path=/tmp/mia/reportes/disco1.jpg -name=disk

rep -id=202a -Path=/tmp/mia/reportes/mbr2.jpg -name=mbr
rep -id=202a -Path=/tmp/mia/reportes/disco2.jpg -name=disk

rep -id=203a -Path=/tmp/mia/reportes/mbr3.jpg -name=mbr
rep -id=203a -Path=/tmp/mia/reportes/disco3.jpg -name=disk
   
#sistema de archivos ext2
mkfs -type=fast -id=201a
pause