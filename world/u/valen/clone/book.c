//by tianlin 2001.5.1
//��һ��ָ�������޸Ĺ�.��bigu���ָ��,���Ѽ�����xfull������.
//by angela@mhxy.2001.12.25

#include <ansi.h>
inherit ITEM;
inherit F_AUTOLOAD;


void create()
{
        set_name(WHT"������"NOR, ({"book"}) );
        set_weight(10);
        set("no_steal", 1);
        set("no_beg", 1);
        set("no_sell", 1);
        set("no_give",""HIW"�����衡�ɡ�ѩ"HIM"����أ�����شӿ���ƮȻ������"NOR"����ס����֣�˵������С���ѣ�
������ǲ���������˵�Ŷ����ת�ۼ�"HIW"��"HIM"�Ѿ���ʧ��������¹��С�\n\n");
        set("no_get", 1);
        set("no_drop",""HIW"�����衡�ɡ�ѩ"HIM"����أ�����شӿ���ƮȻ������"NOR"���������ƨƨ������������һ�ţ�
��������˵�������ۣ������û���ĵģ�������ı����㶼���Ӱ���˵��"HIW"�����衡�ɡ�ѩ"HIM"����ʧ��������¹�֮���ˡ�\n\n");
        set("long",@LONG
�����λ����ε���ʦ������һ������,�������ÿɴ���,��������(kan)������!
LONG );
        if( clonep() )
                        set_default_object(__FILE__);
        else
       {
                set("unit", "��");
                set("material", "unknow");
        }
}

void init()
{
        add_action( "kan_book", "kan" );
        add_action( "body_recover", "xfull");
        add_action( "cloud_goto", "flyto");
}

/* int query_autoload()
{
        return 1;
}*/

//����
int kan_book()
{
        object me;
        me=this_player();
        tell_object(me,
    "������                       ����

������(xfull)       �����ָ�������������ʦ�Ļָ�ָ��\n

���(flyto)         ����ȥ�ĵط�����ʦ��gotoָ��\n");
        return 1;
}

// ���

int cloud_goto(string arg)
{
        string home;
        object mme;
        int goto_inventory = 0;
        object obj;
        string msg;
        mme=this_player();
        if( !arg ) return notify_fail("��Ҫȥ���\n");

        if( sscanf(arg, "-i %s", arg) ) goto_inventory = 1;

        if( !arg ) return notify_fail("��Ҫȥ���\n");

        obj = find_player(arg);
        if(!obj) obj = find_living(arg);
        if(!obj || !mme->visible(obj)) {
                arg = resolve_path(mme->query("cwd"), arg);
                if( !sscanf(arg, "%*s.c") ) arg += ".c";
                if( !(obj = find_object(arg)) ) {
                        if( file_size(arg)>=0 )
                                return mme->move(arg);
                        return notify_fail("û�������ҡ������ط���\n");
                }
        }

        if(!goto_inventory && environment(obj))
                obj = environment(obj);

        if( !obj ) return notify_fail("������û�л������� goto��\n");
        tell_object(mme,HIM"��һ����������,ֻ����ǰ���Ʒɹ�,���߷�������� .
.\n\n"NOR);
        tell_object(mme,"���,��ʹ��,��ˬ,ˬ����!\n\n");
        mme->move(obj);

        tell_object(mme,"������ƻ����½�,��ߴһ��,��!��ȫ��½...\n");
        return 1;
}
// �ָ�
int body_recover()
{
    object mme;
    mme=this_player();
    mme->set("sen",mme->query("max_sen"));
    mme->set("eff_sen",mme->query("max_sen"));
    mme->set("kee",mme->query("max_kee"));
    mme->set("eff_kee",mme->query("max_kee"));
    mme->set("force",mme->query("max_force"));
    mme->set("mana",mme->query("max_mana"));
    mme->set("food",mme->max_food_capacity()*2);
    mme->set("water",mme->max_water_capacity()*2);
    tell_object(mme,"���,̫����,�����ȫ������[5m[1;36m����![2;37;0m\n");
    return 1;
}
void owner_is_killed() {

        write(HIY"ֻ����ǰ���һ��...������.....\n"NOR);
        destruct(this_object());
}