// mihun.c �Ի���
#include <ansi.h>

inherit SSERVER;

void free(object target);

int cast(object me, object target)
{
	string msg;
	string id;
	int success, ap, dp, ap2, ap3, ap4, dp2, dp3, dp4,howlong;

	if( !target ) target = offensive_target(me);
 

	if( !target
	||      !target->is_character()
	||      target->is_corpse()
	||      target==me)
		return notify_fail("������˭�Ļꣿ\n");  

	if(target->query_temp("no_move"))
	return notify_fail(target->query("name")+"�Ѿ��겻���ᣬ����ľ���ˣ�\n");  
  
	msg = HIC
"$N��ͷ�������˾����ģ���̧��ͷ����$n���ĵ�һЦ��\n" 
NOR;

	success = 1;
	ap = me->query_skill("spells");
	ap = ap * ap * ap /12 ;
	ap += (int)me->query("daoxing");
	dp = target->query("daoxing");
//	if( random(ap + dp) < dp ) success = 0;
//here we compared exp and spells level. 
//note: has nothing to do with target's spells level.

	ap2 = (int)me->query_per();
	dp2 = (int)target->query_per();
//	if( random(4*ap) < ((int)target->query_cps()+dp)) success = 0;
//here we compare per and guy's ding li.


	ap3 = (int)me->query("mana");
	dp3 = (int)target->query("mana");
	if( random(ap + dp + 2500*(ap2+dp2)+200*(ap3+dp3)) < (dp+2500*dp2+200*dp3) ) success = 0;

//here we compare current mana. this is important. you need recover to try again.

	if(success == 1 ){
		msg +=  HIR "$n������ؿ���$N������ϧ��֮����Ȼ���𣬾�Ȼ�����Լ���ս��֮�С�\n" NOR;
		//target->set_temp("no_move", 1);
	id=me->query("id");
	target->command("kiss " + id); 
	target->command("follow " +id); 
	target->command("defense " +id); 
	
		howlong = random((me->query_skill("spells") -100))+1;
		if(howlong<60) howlong=60;
		call_out("free", howlong, target);
	}	    
	else {
		msg +=  HIR "$n��Ϊ���������ж������飡\n" NOR;	
		if( living(target) ) target->kill_ob(target);
	} 

	message_vision(msg, me, target);

	return 1;
}

void free(object target)
{
	if (target){
		target->kill_ob(target);
		//target->delete_temp("no_move");  
	}    
	return;
}

