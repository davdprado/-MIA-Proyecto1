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

struct Inodo_Table
{
    int i_uid;
    int i_gid;
    int i_size;
    int i_block[15];
    char i_type;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
};
struct Content
{
    char b_name[12];
    int b_inodo;
};

struct Carpet_Block
{
    Content b_content[4];
    char b_contentf[10];
    char tipo;
};

struct File_Block
{
    char b_content[10];
};

struct Apuntadores_Block
{
    int b_pointer[16];
};

typedef struct
{
    char journal_operation_type[12];
    int journal_type;
    char journal_name[100];
    char journal_content[100];
    time_t journal_date;
    int journal_owner;
    int journal_permissions;
} Journal;