// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
#include <room.h>
inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", "[33m灵霄宝殿[m");
  set ("long", @LONG
这里就是玉帝所在的灵霄宝殿了.殿上当真是霞光万道,瑞气千条.
仙官仙将们列在一旁,北上处正是玉帝老儿的宝座.
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"dianmen.c",
  "northup" : __DIR__"dian.c",
]));


  set("objects", ([ /* sizeof() == 1 */
]));

  setup();
}

int valid_leave(object me, string dir)
{  object *inv, container;
    int sizeinv;
  if (dir !="northup")
   return ::valid_leave(me, dir);
   
     if (dir == "northup") 
     inv=all_inventory(me);
     sizeinv=sizeof(inv);
    while (sizeinv--)
   {
       if (userp(inv[sizeinv]))
       {
     container=inv[sizeinv];
     break;
       }
       if (inv[sizeinv]->is_container())
       {
     container=inv[sizeinv];
     break;
       }
       continue;
   }
   if (container)
   {
       message_vision(HIC"空中传来柳随风的声音：你带着那"+container->name()+
           HIC"进去干什么！？想蒙混过关？？\n"NOR,me);
        return notify_fail("");

    }
     return ::valid_leave(me, dir);
 
   }


