
#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
	set_name( HIR "����һ��ľͷ������Ƭ" NOR, ({ "rustysword" }) );
	set_weight(7000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�Ѱ���һ��ľͷ������Ƭ������������ߣ�\n");
		set("value", 1);
		set("no_get",1);
		set("no_drop",1);
		set("material", "steel");
		set("wield_msg", "$N�ѱ�������$n�γ��������С�\n");
		set("unwield_msg", "$N�����е�$n�������䡣\n");
	}
	init_sword(85);
	setup();
}
void init()
{
	add_action("do_make","remake");
}
int do_make()
{
	object me;
	object obj;
	me=this_player();
	obj=new(__DIR__"box");
	obj->move(me);
	if(query("equipped")) unequip();
	tell_object(me,"�㽫���е�"+query("name")+"�ֲ𿪣���ɸ����ӡ�\n");
        destruct(this_object());
	return 1;
}          