#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <list>

struct Particion
{
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
};

struct MBR
{
    int mbr_tam;
    time_t mbr_fecha;
    int mbr_disk_asignature;
    Particion mbr_partition[4];
};

struct EBR
{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
};

struct Espacio
{
    int espaciolibre;
    int bytestart;
};

struct partmount
{
    char id[16];
    char nombre[16];
};

struct Super_Block
{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
};
