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
                "north" : "/d/city/ximen", 
        ]));

        set("objects", 
        ([ //sizeof() == 1 
				"/u/dick/clone/yinshen": 1, 
                "/d/city/obj/jia" : 1, 
                "/d/city/obj/jia2" : 1, 
        ]));


        set("outdoors", "changan");
	set("no_clean_up", 0);
        setup();
	replace_program(ROOM);
}



