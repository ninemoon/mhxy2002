//By waiwai@mszj 2000/10/26

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIB"Ұ����ҽ��"NOR);
        set("long", 

"\n��������վ��Ұ����ҽ��������������˶�����Ҫ��̬�� \n"+
"�ſ�վ��һ���շѵ�С��......��������һ������ "+HIR"(paizi)\n\n"NOR

        );
	set("item_desc", ([
		"paizi": HIC"��Ҫ��̬�� "+HIR"\"give 5000 gold to er\" \n\n"NOR,
	]));

        set("exits", ([
                "south" : "/d/changan/wside5",
               
         ]) );

        set("objects", ([
		__DIR__"npc/xiaoer" : 1,
        ]));

        set("no_kill", 1);
        set("no_bian", 1);

        setup();
}