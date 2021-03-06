//[4;53m[1;31mBy tianlin@mhxy for 2001.9.27[2;37;0m

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("张松溪", ({ "zhang songxi", "zhang" }));
	set("nickname", HIW"武当"NOR+HIR"四侠"NOR);
	set("long", 
		"他就是张三丰的四弟子张松溪。\n"
		"他今年四十岁，精明能干，以足智多谋著称。\n");
	set("gender", "男性");
	set("age", 40);
	set("attitude", "peaceful");
	set("class", "wudang");
	set("shen_type", 1);
	set("str", 26);
	set("int", 30);
	set("con", 26);
	set("dex", 28);
	
	set("max_kee", 1200);
	set("max_sen", 800);
	set("force", 1500);
	set("max_force", 1500);
	set("mana", 1500);
	set("max_mana", 1500);
       set("force_factor", 100);
       set("mana_factor", 90);
	set("combat_exp", 100000);
	set("daoxing", 100000);

	set_skill("force", 90);
	set_skill("wudang-force", 90);
	set_skill("dodge", 90);
	set_skill("tiyunzong", 90);
	set_skill("unarmed", 90);
	set_skill("taiji-quan", 95);
	set_skill("parry", 95);
	set_skill("sword", 90);
	set_skill("spells", 90);
	set_skill("taiji-jian", 90);
	set_skill("wudang-xianfa", 80);
	set_skill("literate", 90);

	map_skill("force", "wudang-force");
	map_skill("spells", "wudang-xianfa");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");

	create_family("武当派", 2, "弟子");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
}
void attempt_apprentice(object ob)
{
        if ( ((int)ob->query("combat_exp") < 50000)) {
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应在道德及武功方面多下努力，来日方长吗！");
                return;
        }
        if ((int)ob->query_skill("wudang-force", 1) < 30) {
                command("say 我武当派乃内家武功，最重视内功心法。");
                command("say " + RANK_D->query_respect(ob) +
                        "是否还应该在太极神功上多下点功夫？");
                return;
        }
        command("say 好吧，我就收下你了。");
        command("recruit " + ob->query("id"));
}
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "wudang");
                ob->set("title", "[1;33m武当派[1;37m第[1;36m三[1;37m代弟子[2;37;0m");
}
