#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon;
              int i,j,k,u,damage;
              weapon = me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("你要攻击谁？\n");
        if(!me->is_fighting())
                notify_fail("你们没有在打架！\n");

        if(me->query("family/family_name")!="蜀山派")
                notify_fail("不是蜀山的！\n");
           
		 k=300;
         j=50; 
u=9;

me->delete("env/brief_message");
target->delete("env/brief_message");
message_vision(HIC"\n$N仰天大喝了一声：\n"NOR,me,target);
message_vision(HIW"\n万～～～～剑～～～～决\n"NOR,me,target);
message_vision(HIC"\n一刹那间千万剑光破空而来，劈面罩向$n\n"NOR,me,target);
for (i=0;i<=u;i++)
{ 

message_vision(HIY"\n$n一个不慎，中了一剑\n"NOR,me,target);
damage=100+random(k);
target->receive_damage("kee",damage);
target->receive_wound("kee",damage/3);
COMBAT_D->report_status(target); 
}
  
  
    me->start_busy(1);
	return 1;
}
