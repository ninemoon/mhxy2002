// fenshen.c 分身术

inherit SSERVER;

int cast(object me, object target)
{
	int fenshen_time; //this time is the time interval fenshen can be used again. 
	object soldier;
 
	fenshen_time=60+(200-(int)me->query_skill("spells"));
	if(fenshen_time<60) fenshen_time=60;
	
	 

	message_vision("$N喃喃地念了几句咒语。\n", me);
 

	seteuid(getuid());
	soldier = new("/obj/npc/jiashen");

	soldier->move(environment(me));
	soldier->invocation(me);
	soldier->set_temp("invoker",me); 
	me->start_busy(1);

	return 8+random(5);
}
