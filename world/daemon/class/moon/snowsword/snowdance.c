//��ѩ snowdance 

#include <ansi.h>
 
inherit F_DBASE;
inherit SSERVER;
 
void remove_effect(object me, object target, int amount);
 
int perform(object me, object target)
{
        int skill_sword, skill_dodge, dodge_amount,attack_amount;

       
        skill_dodge = 300;             
        skill_sword = 300;      
		
        me->add("force", -50);
        message_vision(
                HIW"$N��һ�����������Ṧ���ν����衣ֻ��$N�㲻մ�أ����н�Խ��Խ�죬�𽥻���һ�Ű������ù�����\n" NOR, me);
 
        attack_amount=skill_sword*random(6)/10;
        dodge_amount=skill_dodge*(5+random(6))/10; 
        me->add_temp("apply/attack", -attack_amount);  
        me->add_temp("apply/dodge",dodge_amount);  //trade offense for defense.  
        
         return 1;
}
 
void remove_effect(object me, int dodge_amount,int attack_amount)
{
        me->add_temp("apply/dodge", -dodge_amount);
        me->add_temp("apply/attack", attack_amount);
        me->delete_temp("powerup");
        message_vision(HIW"$N����������֧�����ò������Ų����Ż����С�\n"NOR,me);
}

