#include <ansi.h>
#include <combat.h>
inherit SSERVER;
void remove_effect(object me, int amount);
int cast(object me, object target)
{
	if( (int)me->query("force") < 50 )
		return notify_fail("你的真气不够。\n");

	if( (int)me->query("mana") < 500 )
		return notify_fail("你的法力不够。\n");

	write( HIW "$N化五行之气为己用，精气神立刻为之一振。\n" NOR);

	me->receive_curing("kee", 10 + (int)me->query_skill("force")/5 );
	me->receive_curing("sen", 10 + (int)me->query_skill("force")/5 );
	me->add("force", -50);
	me->add("spells", -500);
	me->set("force_factor", 0);
	me->set("mana_factor", 0);

	return 1;
}
