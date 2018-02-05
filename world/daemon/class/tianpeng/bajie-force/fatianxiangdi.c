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
                HIC "$N猛吸一口气，运起八戒心法，全身闪起点点"BLINK+HIY"金光"NOR+HIC"，只见$N的身体慢慢的变大了!\n" NOR, me);

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
        tell_object(me, HIB"$N的八戒心法运行一周天完毕，接着身体变了回来。\n"NOR);
}

