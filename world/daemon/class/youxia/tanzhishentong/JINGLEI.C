// jinglei.c ��ָ����
 
#include <ansi.h>
 
inherit SSERVER;
 
int perform(object me)
{
	string msg;
	object weapon, weapon2, target;
	int skill, dp, wound;

	target = me->select_opponent();

        skill = me->query_skill("tanzhishentong",1);

	if( !(me->is_fighting() ))
                return notify_fail("��"HIG"��ָ����"NOR"��ֻ����ս����ʹ�á�\n");

	if ( objectp(weapon = me->query_temp("weapon")))
                return notify_fail("��"HIG"��ָ����"NOR"���������ʹ�á�\n");

	if( skill < 100)
                return notify_fail("��ĵ�ָ��ͨ�ȼ�����, ����ʹ�á�"HIG"��ָ����"NOR"����\n");

        if( me->query("force") < 150 )
                return notify_fail("��������������޷����á�"HIG"��ָ����"NOR"����\n");
 
message_vision(HIC"$Nʹ����ָ��֮ͨ"HIG"����ָ���ס�"HIC", ��ʱ���ھ��Ⱪ�䣬���ֹ���$n��ȫ��Ѩλ��\n"NOR,me,target); 
 
	dp = target->query("combat_exp");
	if( dp < 1 )
		dp = 1;
	if( random(me->query("combat_exp")) > random(dp)) 
	{
		if(userp(me))
                        me->add("force",-150);
message_vision( HIR"$nֻ������ǰһ��������Ѩ��΢΢һʹ��ȫ��������й������\n"NOR,me,target); 
        weapon = target->query_temp("weapon");
                 if(objectp(weapon))
                {
message_vision(HIR"ͬʱ����һ�飬�����������ֶ�����\n"NOR,me,target); 
                       weapon->move(me);
               }
		wound = 300 + random(200);
                if((int)target->query("force") < wound)
                        wound = target->query("force");
                target->add("force", -wound);
                target->receive_wound("sen", wound/5);
		target->start_busy(4);
		me->start_busy(1);
		COMBAT_D->report_status(target);

	}
	else
	{
                msg = HIC"����$n�Ŀ�����$N����ͼ�����̲�ȡ���ƣ�ʹ$P�ġ���ָ���ס�û�������á�\n"NOR;
		me->start_busy(2);
	}

	if(!target->is_fighting(me)) target->fight_ob(me);

	return 1;
}