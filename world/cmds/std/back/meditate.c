//By tianlin@mhxy for 2002.1.17

#include <skill.h>

inherit F_CLEAN_UP;

int finish(object me, int sen_cost);

int main(object me, string arg)
{
        int sen_cost, busy_time;

        seteuid(getuid());
        
        if(environment(me)->query("no_fight") || 
           environment(me)->query("no_magic") )
              return notify_fail("��ȫ���ڽ�ֹ������\n");
                        
        if (me->is_busy() || me->query_temp("pending/meditating"))
                return notify_fail("��������æ���ء�\n");

	if( me->is_fighting() )
		return notify_fail("ս���в���ڤ˼��\n");

	if( !stringp(me->query_skill_mapped("spells")) )
		return notify_fail("��������� enable ѡ����Ҫ�õķ�����\n");

        if( !arg
        ||      !sscanf(arg, "%d", sen_cost) )
                return notify_fail("��Ҫ�����پ���ڤ˼��\n");
        if( sen_cost < 10 ) return notify_fail("������Ҫ�� 10�㡸�񡹲���ڤ˼��\n");

      if( (int)me->query("sen") < sen_cost )
                return notify_fail("���������ǲ���,����������Ƿ��ˡ�\n");

        if( (int)me->query("kee") * 100 / (int)me->query("max_kee") < 70 )
                return notify_fail("����������״��̫���ˣ��޷����о���\n");

        me->set_temp("pending/respirate", 1);
        write("����ϥ����������ڤ˼��һ�����\n");

        me->receive_damage("sen", sen_cost);
        if(busy_time<0) busy_time=0;
        me->start_busy(1);

        call_out("finish", 1, me, sen_cost);
        return 1;
}

int finish(object me, int sen_cost)
{
        int mana_gain;

        // This function ranged from 1 to 15 when sen_cost = 30
        mana_gain = sen_cost * ((int)me->query_skill("spells") / 15 + (int)me->query_spi() ) / 30;
        me->set_temp("pending/respirate", 0);
        if( mana_gain < 1 ) {
                tell_object(me, "���ǵ��������۾���ֻ��������һƬ�հס�\n");
            me->start_busy(1);
                return 1;
        }

        me->add("mana", mana_gain );
        tell_object(me, "���й���ϣ���ڤ˼�лع�������\n");

                if( (int)me->query("mana") > (int)me->query("max_mana") * 2) {
                        if( (int)me->query("max_mana") >=
              (int)me->query_max_mana() ) {
                        tell_object(me, "����ķ������ӵ�˲�����Ȼ��������һƬ���ң��ƺ������������Ѿ�����ƿ����\n");
                } 
                else {
                                tell_object(me, "��ķ�����ǿ�ˣ�\n");
                                me->add("max_mana", 1);
if ( (int)me->query("max_mana") > (int)me->query("maximum_mana"))
me->set("maximum_mana", (int)me->query("max_mana"));
                        }
                        me->set("mana", me->query("max_mana"));
                }

          me->start_busy(1);
        return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ : meditate|mingsi [<�ķѡ��񡹵�����Ԥ��ֵ 30>]
 
����ڤ˼��������ľ�������Ч�ؼ������۳��ܹ�����ʩչ����������
�����������Լ��ķ�����

��ο� help stat 
HELP
        );
        return 1;
}
