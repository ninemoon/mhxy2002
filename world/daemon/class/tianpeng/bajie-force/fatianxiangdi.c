//by valen 2001.7.28 

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;


        skill = me->query_skill("bajie-force",1);

	if( skill < 250 ) {
		skill=250;
	}
 
 

        me->add("force", -skill);
        me->receive_damage("kee", 50);

        message_vision(
                HIC "$N����һ����������˽��ķ���ȫ��������"BLINK+HIY"���"NOR+HIC"��ֻ��$N�����������ı����!\n" NOR, me);

        me->add_temp("apply/attack", skill );
		me->add_temp("apply/strength", skill );
        me->set_temp("powerup", 1);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/5 :), skill);
 
        return 1;
}

void remove_effect(object me, int amount)
{
        if(!me) return;
        me->add_temp("apply/attack", - amount);
	me->add_temp("apply/strength", - amount);
        me->delete_temp("powerup");
        me->add("bellicosity", amount*2 );
	// mon 3/1/98. move this to after powerup is done.
        tell_object(me, HIB"$N�İ˽��ķ�����һ������ϣ�����������˻�����\n"NOR);
}

