//shushan-force--heal.c by yushu 2000.11
#include <ansi.h>
int exert(object me, object target)
{
        if( me->is_fighting() )
                return notify_fail("ս�����˹����ˣ�������\n");

        if( (int)me->query("force") < 50 )
                return notify_fail("�������������\n");

        if( (int)me->query("eff_kee") < (int)me->query("max_kee") / 2 )
                return
notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

        write( HIM "��������ɽ�ķ�,��������ʼ���ˡ�\n" NOR);
        message("vision",
                HIM + me->name() +
"������ɽ�ķ�,��������ʼ����,���ã��³�һ����Ѫ����ɫ�������ö��ˡ�\n"
NOR,
                environment(me), me);

        me->receive_curing("kee", 10 + (int)me->query_skill("force")/5 );
        me->add("force", -50);
        me->set("force_factor", 0);

        return 1;
}

