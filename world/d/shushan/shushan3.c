//shushan.3 by yushu.2000.11
inherit ROOM;
#include <ansi.h>
void create ()
{
  set ("short",HIR "��" HIG "��üɽ" HIR "��" NOR);
  set ("long", @LONG
������ͨ����ɽ�ɵ�ɽ·��·��᫲�ƽ���Ա߾���ɽ�£�
����һ�������ɵ�ͷ��Ŀѣ����Ͻ������۾�������һ������
��ˤ�÷�����ǡ�
LONG);

  set("outdoors", 2);
  set("exits", ([ /* sizeof() == 2 */
  "southwest" : "/d/shushan/shushan2",
  "southup" : "/d/shushan/shushan4", 
]));

  setup();
}





