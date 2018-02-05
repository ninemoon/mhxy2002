//changan city

inherit ROOM;

void create ()
{
        set ("short", "长安城i");
        set ("long", @LONG

这里是长安城的i。 
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
                "west" : "/d/westway/west1",
                "east" : __DIR__"baihu-w3",
                "north" : "/d/city/ximen",
                "out" : "/d/city/ximen",
                "northwest" : "/d/wudang1/wdroad4",
				"change" : "/d/moon/npc/change" ,
                "jia" : "/d/city/obj/jia"  ,
                "iii" : "/d/city/iii"  ,
        ]));

        set("objects", 
        ([ //sizeof() == 1
                __DIR__"npc/wujiang" : 1, 
                "/d/city/obj/jia" : 1,
                //"/d/moon/npc/change2" : 1,
                "/d/moon/npc/change" : 1,
				__DIR__"npc/bing" : 3, 
				__DIR__"npc/qian" : 1, 
        ]));


        set("outdoors", "changan");
	set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}



