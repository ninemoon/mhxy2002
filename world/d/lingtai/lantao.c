// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// Room: some place in 西牛贺洲
// forrest.c

inherit ROOM;

void create()
{
  set ("short", "[32m松树林[m");
  set ("long", @LONG

松林之中非常的暗，光线全被如伞如盖的树枝挡住。地下布
满枯枝，每走一步都会发出很翠的响声，不时可看到几个砍
柴的道士。
LONG);
set("exits", ([ /* sizeof() == 4 */
"northdown" : __DIR__"baixi2",
"south" : __DIR__"lantao1",
"westup" : __DIR__"lantao2",

]));
set("objects", ([ /* sizeof() == 2 */
"/d/lingtai/obj/shuzhi": 1,
"/d/lingtai/npc/kancai": 2
]));
        set("no_clean_up", 0);
   set("outdoors", 1);
        setup();
        replace_program(ROOM);
}


