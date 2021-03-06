// link 2001.2.19
//By tianlin@mhxy for 2002.1.18加入rumor系统
#include <ansi.h>
#include <skill.h>
#include <weapon.h>
#include <combat.h>

void remove_effect(object me, int a_amount, int d_amount);

inherit SSERVER;
int perform(object me, object target)
{
        string str;
        object weapon,ob;
        int skill, damage, ap, dp, kar;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )

                return notify_fail("「娇阳似火」只能在战斗中使用。\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "umbrella")
                return notify_fail("「娇阳似火」必须用伞才能施展。\n");

        if( (int)me->query_skill("lingfan-san", 1) < 90 )
                return notify_fail("你的「灵幡九阴伞」不够娴熟，不会使用「娇阳似火」。\n");
        if( (int)me->query("force") < 600  ) 
                return notify_fail("你的内力不够。\n");
        if(!wizardp(me) && me->query("family/family_name")!="灵界")
                return notify_fail("你非灵界弟子，无法使用「骄阳似火」。\n");


        skill = me->query_skill("lingfan-san");
        weapon = me->query_temp("weapon");
        msg = MAG "$N清啸一声,使出「灵幡九阴伞」中的绝技「娇阳似火」手中的"+weapon->name()+MAG"疯魔般地扫向$n！\n"NOR;
        message_vision(msg, me, target);

        me->add("force", -300);

        me->clean_up_enemy();
        ob = me->select_opponent();
        damage=weapon->query("weapon_prop/damage");
        ap = me->query("combat_exp") + skill * 100 + me->query("daoxing") + me->query("con") * 1000; 
        dp = target->query("combat_exp") + target->query_skill("parry") * 100 + target->query("daoxing") 
             + target->query("kar") * 1000; 
        kar = me->query("kar");
        
        if(ap > dp) {
          msg = HIY"●娇●！\n"NOR;
          message_vision(msg, me, target);
          target->add("kee", -damage);
          target->add("eff_kee", -damage/2);
          COMBAT_D->report_status(target, 0);
        }
        if(ap > dp) {
          msg = HIR"●阳●！\n"NOR;
          message_vision(msg, me, target);
          if(random(1) == 0) target->add("kee", -damage);
          else target->add("kee", -damage*2);
          COMBAT_D->report_status(target, 0);
          me->improve_skill("lingfan-san", 1, 1);
        }
        if(ap > dp) {
          msg = HIY"●似●！\n"NOR;
          message_vision(msg, me, target);
          if(random(5) == 0) target->add("kee", -damage);
          else target->add("kee", -damage*3);
          COMBAT_D->report_status(target, 0);
          me->improve_skill("lingfan-san", 1, 1);
        }
        if(ap > dp) {
          msg = HIR"●火●！\n"NOR;
          message_vision(msg, me, target);
          if(random(10) == 0) target->add("kee", -damage);
          else target->add("kee", -damage*4);
          COMBAT_D->report_status(target, 0);
          me->improve_skill("lingfan-san", 1, 1);
        }
        if( me->is_fighting() ) me->start_busy(random(2)+1);
   if (target->query("eff_kee")<0 || !living(target))  
                       {str=target->name()+"被"+me->name()+"用灵界绝招[1;37m「娇阳似火」[2;37;0m[1;35m给杀死了. 尸体已经不堪入目！";
	                message("channel:rumor",HIM"【谣言】某人："+str+"\n"NOR,users());
	               }
        return random(3)+5;
}
