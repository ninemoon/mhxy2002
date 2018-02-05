// jia.c �ɻ���Ҷ��
#include <mudlib.h>
#include <ansi.h>
#include <armor.h>
#include <command.h>
#define NULL_VALUE 0
inherit CLOTH;
inherit F_SAVE;
inherit F_AUTOLOAD;
inherit F_DAMAGE;

string inputstr,verb;
void create()
{
       seteuid(getuid());
       set("long",@LONG
               �ɻ���Ҷ��
����������������������������������������������������������
�� ������ ��     ��        ��   ��     ��       ��      ��
����������������������������������������������������������
��pk      ��pk<ob> with <id>    ����ĳ��ɱĳ��          ��
��xing    ��xing <id>           ����ĳ������            ��
��yun     ��yun  <id>           ����ĳ���ε�            ��
��qshs    ��qshs <id>           ����������(�ָ�ԭ�书)  ��
��feng    ��feng <id>           ���ⶳĳ��              ��
��jiefeng ��jiefeng <id>        �����ĳ��              ��
��quanjia ��quanjia <id>        ����ĳ�˲��ٴ�ܣ�      ��
��pk      ��pk <id> with <id>   ����ĳ�˿�ʼ������һ��  �� 
��yao     ��yao<����><Ǯ������> ����������ĳ��Ǯ����������
����������������������������������������������������������
LONG
       );
       set("unit","��");
       set("no_get",0);
       set("no_give",0);
       set("material", "cloth");
       set("armor_prop/armor", 300);
       set("light",1);
       setup();
}

void init()
{
       seteuid(geteuid());
       set_name(HIY "�ɻ���Ҷ��" NOR, ({ "jia", "ander" }));
       add_action("do_change","change"); 
       add_action("wave","yao");  
       add_action ("pk_mob", "pk");
       add_action ("do_wakeup", "xing");  
       add_action ("do_hun","yun");       
       add_action ("do_reincarnate","qshs");
       add_action ("do_disable_player","feng");
       add_action ("do_enable_player","jiefeng");
       add_action ("do_gan","gan");
       add_action ("do_halt","quanjia");
       this_player()->set_temp("heat",1);
}

int do_change(string arg)
{
  object fd,me;
  me=this_player();
  if (arg!=NULL_VALUE){
    fd = LOGIN_D->find_body(arg);
    if (!fd) return notify_fail("����û�����ѽ��\n");
    }
  if (arg) {
    if(arg=="ken") return notify_fail("�󵨣�\n");
    if(fd->query("gender")=="Ů��") fd->set( "gender", "����" );
    else fd->set( "gender", "Ů��" );
    message("shout", MAG "��ң�ԡ�ĳ�ˣ�" + HIG + "��˵" + me->query("name") + "�ɹ��Ķ�" 
       + fd->query("name") + "������һ�α���������\n" NOR,users());
    fd->save();
    write(MAG"��������ˣ�\n"NOR);
    return 1;
  }
}

int wave (string arg)
{
        string kind;
        int amount;
        object n_money;

        if( !arg || sscanf(arg, "%d %s", amount, kind)!=2 )
          return notify_fail("usage: yao <����Ǯ> <Ǯ������>\nע�������ȱ���������Ǯ��");

        n_money = present(kind + "_money", this_player());
        if( !n_money && file_size("/obj/money/" + kind + ".c") < 0 )
                return notify_fail("�����û�У�Ҫ��ƨѽ��\n");
        if( amount < 1 )
                return notify_fail("�ٺ٣�����û�С�\n");

        if( !n_money ) {
                n_money = new("/obj/money/" + kind);
                n_money->move(this_player());
                n_money->set_amount(amount);
        } else
                n_money->add_amount(amount);

message_vision( sprintf(HIY "$Nʹ�����ͱ��˵Ŀڴ���ͻȻ�Ӵ������ͳ�%s%s%s��\n" NOR,
                        chinese_number(amount),
                        n_money->query("base_unit"),
                        n_money->query("name")),
                       this_player());
               return 1;
}

int pk_mob(string str)
{
        object ob1,ob2;
        string st1,st2;
        if (!str || str=="") return notify_fail ("������˭ PK ˭��\n");
        if (sscanf( str,"%s with %s",st1,st2)!=2 )
           return notify_fail ("pk <ob1> with <ob2>\n");

        if (!ob1=present(st1,environment(this_player())))
          return notify_fail("�Ҳ��� "+st1+" �������.\n");

        if (!ob2=present(st2,environment(this_player())))
          return notify_fail("�Ҳ��� "+st2+" �������.\n");
          if (st1=="ken" || st2=="ken")
              return notify_fail ("��,�㲻�����!\n");

       message_vision(HIR ""+ob1->name()+"����"+ob2->name()+"���һ����������������\n" NOR,
       this_player());
               ob1->kill_ob(ob2);
               return 1;
}

int do_wakeup (string str)
{
  object who;

  if (!str) return notify_fail ("usage:xing <id>\n");
  who = LOGIN_D->find_body(str);
  if (!who){ 
  if (!(who=present (lower_case(str), environment(this_player()))) )
    return notify_fail ("����û��"+str+"\n");
  }
  who->remove_call_out("revive");
  who->revive();
  write("Ok.\n");
  return 1;
}

int do_hun (string str)
{
  object who;

  if (!str) return notify_fail ("�����ӻ��ˣ���ô���԰��Լ�Ū�Σ�\n");
  if (str=="ken") return notify_fail ("�����Ļ���suicide -f�����һ��!\n");
  who = LOGIN_D->find_body(str);
  if (!who){ 
  if (!(who=present (lower_case(str), environment(this_player()))) )
    return notify_fail ("����û��"+str+"\n");
  }

  who->remove_call_out("unconcious");
  who->unconcious();
  who->announce();
  write("Ok.\n");
  return 1;
}

int do_reincarnate (string str)
{
  object ob;
  if (!str) return notify_fail("usage: qshs <id>\n");
       ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("���������?\n");
  if (ob->is_ghost()) 
           tell_object(ob,"�������ȫ������...\n");
       else 
           return notify_fail("��...����˺����ǻ�ģ�\n");
  tell_object(ob,"�����ϣ����ǹ�!��Ҫ���㸴��ұ����ϴε�һ�С�\n");
  tell_room(environment(ob),"һ�����ͻȻ��������£�������"+
       (string)ob->query("name")+"����Χ��\n", ob);
  tell_object(ob,"ͻȻһ����������������𣬡������....��������\n��ʼ���ٲ��ǻ���ˡ�����ͻȻ�е�һ�����...\n");
  ob->reincarnate();
  ob->query_temp("last_damage_from");  
  tell_object(ob,"�ܺã����ָ����ˣ�\n");
  write("Ok.\n");
  return 1;    
}

int do_disable_player (string str)
{
  object ob;
  if (!str) return notify_fail("usage: feng <id>\n");
  if (str=="ken") return notify_fail("��ɲ����������!\n");
       ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("���������?\n");
  tell_object(ob,"ͻȻ����۾�һƬģ��...\n");
  ob->set_temp("block_msg/all",1);
  write("Ok.\n");
  return 1;    
}

int do_enable_player (string str)
{
  object ob;
  if (!str) return notify_fail("usage: feng <id>\n");
       ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("���������?\n");   
  ob->set_temp("block_msg/all",0);
  ob->enable_player(); 
  tell_object(ob,"�����������˵��������ټ��ټ�ܡ������ָֻ���...\n");
  write("Ok.\n");
  return 1;
}

int do_halt (string str)
{
  object ob;
  if (!str) return notify_fail("usage: quanjia <id>\n");
       ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("�����޴��ˣ�\n");       
  if( !ob->is_fighting() )
       return notify_fail("�������ڲ�û�д��С�\n");        
  tell_room(environment(ob),HIY "����к�Ȼ������������Х�ߴ����Ӱ��\n���Ͱ��Ķ�"+                    
       (string)ob->query("name")+"˵�����������˴������ˣ��ҿ���λ"+RANK_D->query_respect(ob)+"�������˰ɣ���\n" NOR, ob);
  ob->remove_all_killer();
  tell_room(environment(ob),HIC "�ţ�"+                    
       (string)ob->query("name")+"˵��������˵�Ķԣ��Ҳ����ٴ��ˡ���\n" NOR, ob);
  tell_room(environment(ob), "..."+                    
       (string)ob->query("name")+"�����ܵ����٣����������ˣ�\n", ob);
  return 1;    
}
