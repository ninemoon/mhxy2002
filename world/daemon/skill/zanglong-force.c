// ningxie-force.c  �������ķ���

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
        return notify_fail("�����ķ�ֻ����ʦ��ѧ�����Ǵ�����(exert)�����������ȡ�\n");
}
string exert_function_file(string func)
{
        return CLASS_D("yujian") + "/zanglong-force/" + func;
}

int stage(int level)
{
        if( level <10 ) return 1;
        else if ( level < 20 ) return 2;
        else if ( level < 40 ) return 3;
        else if ( level < 70 ) return 4;
        else if ( level < 110 ) return 5;
        else if ( level < 160 ) return 6;
        else if ( level < 220 ) return 7;
        else if ( level < 290 ) return 8;
        else return 9;
}

string level_description(int level)
{
        if ( stage(level) < 3 )
                return BLU "��"+chinese_number( stage(level) )+"�ء�" NOR;
        else if ( stage(level) < 5 )
                return HIB "��"+chinese_number( stage(level) )+"�ء�" NOR;
        else if ( stage(level) < 7 )
                return YEL "��"+chinese_number( stage(level) )+"�ء�" NOR;
        else if ( stage(level) < 9 )
                return CYN "��"+chinese_number( stage(level) )+"�ء�" NOR;
        else 
                return HIW "��"+chinese_number( stage(level) )+"�ء�" NOR;
}
void skill_improved(object me)
{
        //if stage increased, give bonus...?
        int level = (int)me->query_skill("zanglong-force", 1);
        if ( stage(level) == stage(level-1) + 1)
        {
                //this is to prevent ppls from abondoning skill to get bonus.
                if( (int)me->query("zl-force_bonus") < stage(level) )
                {
                        me->set("zl-force_bonus", stage(level));
//                      me->set("max_force", (int)me->query("max_force") + stage(level)*50 );
                        // mon 12/13/98
                        me->set("maximum_force", 
                                (int)me->query("maximum_force") 
                                + stage(level)*50 );
                        me->save();
                        log_file("zanglong-force-bonus", ctime( time() )+": "
                                +me->query("name")+"("+me->query("id")+")"
                                +" got neili "+(stage(level)*50)+".\n");
                        message_vision(HIW "$NͻȻ���������嶥���ؿ�һ��Ѫ����ԭ����$N�Ĳ����ķ������˵�"+chinese_number(stage(level))+"�ؾ��磡\n" NOR, me);

                }
        }
                        
}