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
                return notify_fail("��Ҫ����˭��\n");
        if(!me->is_fighting())
                notify_fail("����û���ڴ�ܣ�\n");

        if(me->query("family/family_name")!="��ɽ��")
                notify_fail("������ɽ�ģ�\n");
           
		 k=300;
         j=50; 
u=9;

me->delete("env/brief_message");
target->delete("env/brief_message");
message_vision(HIC"\n$N��������һ����\n"NOR,me,target);
message_vision(HIW"\n�򡫡�����������������\n"NOR,me,target);
message_vision(HIC"\nһɲ�Ǽ�ǧ�򽣹��ƿն�������������$n\n"NOR,me,target);
for (i=0;i<=u;i++)
{ 

message_vision(HIY"\n$nһ������������һ��\n"NOR,me,target);
damage=100+random(k);
target->receive_damage("kee",damage);
target->receive_wound("kee",damage/3);
COMBAT_D->report_status(target); 
}
  
  
    me->start_busy(1);
	return 1;
}
