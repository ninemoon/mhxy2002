// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
// invocation.c

inherit SSERVER;

int cast(object me, object target)
{   
        int invocation_time;
        object soldier;

        if( !me->is_fighting() )
                 notify_fail("好象没有人要杀你！\n");
   
		if((string)me->query("family/family_name")!="阎罗地府")
                notify_fail("你不是阎罗地府的弟子 \n"); 
			 
        message_vision("$N喃喃地念了几句咒语。\n", me);

        me->add("mana", -50);
        me->receive_damage("sen", 40);

        seteuid(getuid());
        soldier = new("/d/death/npc/hufa");
        soldier->move(environment(me));
        soldier->invocation(me);  
		
        return 8+random(5);
}
