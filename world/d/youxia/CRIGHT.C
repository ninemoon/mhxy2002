#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "右偏院");
  set ("long", @LONG

这是一个可爱的小草坪，草坪上有一圆石桌，桌边有石凳。桌面
是精致大理石，石上刻着一个棋盘。盘上还放着一局未完的残棋
。似乎学习（ｘｉａ）一下可以得到不少知识。桌上还有两杯残
酒，尚有余温。

LONG);
  set("item_desc", ([ /* sizeof() == 1 */
  "canqi" : "一局未完的残棋，棋势奥妙无穷．．．\n",
]));


  set("outdoors", 1);
  set("exits", ([ /* sizeof() == 2 */
    "west" : __DIR__"yard",
]));
 set("objects", ([
__DIR__"obj/canqi" : 1,
__DIR__"npc/oldman" :1,

                       
 ]) );

  setup();
}

void init()
{
        add_action("do_study", "xia");
}

int do_study(string arg)
{       
        object me=this_player();
        int sen_cost, kee_cost, force_cost, gain;

        if( !arg || (arg != "canqi"))
                return notify_fail("你要下什么棋？\n");
        if( me->is_busy() )
                return notify_fail("你忙的很，哪有功夫去研究棋局！\n");
        if( me->is_fighting() )
                return notify_fail("现学现卖已来不及了！\n");
        if( (int)me->query_skill("literate", 1) < 100)
                return notify_fail("你看了半天也看不懂棋盘上面摆了些什么！\n");
        if( (int)me->query_skill("literate", 1) < 180)
                return notify_fail("你看了半天好象虽看出了点下棋的门道，却还不是老人的对手。\n");
        if( (int)me->query_skill("literate", 1) >= 500)
                return notify_fail("老人说道:不用再下了，老夫已经认输了。\n");
        if( (int)me->query("max_force") < 1000)
                return notify_fail("你底气不足，练不了。\n");

        sen_cost = 80 - (int)me->query_int();
        if( (int)me->query("sen") < sen_cost )
                return notify_fail("你现在头晕脑胀怎么下棋，该休息休息了。\n");

        kee_cost = 80 - (int)me->query_con();
        if( (int)me->query("kee") < kee_cost )
                return notify_fail("你现在浑身无力怎么下棋，该休息休息了。\n");

        force_cost = 20;
        if( (int)me->query("force") < force_cost )
                return notify_fail("你现在已提不起气了怎么下棋，该休息休息了。\n");

        me->receive_damage("sen", sen_cost);
        me->receive_damage("kee", kee_cost);
        me->add("force", - force_cost);

        gain = (int)me->query("int")/2 + (int)me->query("con")/2 + 1 + random(10);

        me->improve_skill("literate", gain);

        write("你和老人坐下来开始慢慢的下棋．．．老人拍拍你的肩说道：你的棋艺不错嘛。
[33m你的「读书识字」进步了！[0m\n");

        tell_room( environment(me), me->name() + "似乎正在和老人津津有味下棋．．．\n", ({me}));

        return 1;
}

