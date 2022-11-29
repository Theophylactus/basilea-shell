#include <stdexcept>
#include <iostream>
#include "../Function.h"

#define LAURETANAE "Kyrie, eleison.\n"\
"Christe, eleison.\n"\
"Kyrie, eleison.\n"\
"Christe, audi nos.\n"\
"Christe, exaudi nos.\n"\
"Pater de caelis, Deus, miserere nobis.\n"\
"Fili, Redemptor mundi, Deus, miserere nobis.\n"\
"Spiritus Sancte, Deus, miserere nobis.\n"\
"Sancta Trinitas, unus Deus, miserere nobis.\n"\
"Sancta Maria, ora pro nobis.\n"\
"Sancta Dei Genetrix, ora pro nobis.\n"\
"Sancta Virgo virginum, ora pro nobis.\n"\
"Mater Christi, ora pro nobis.\n"\
"Mater Ecclesiae, ora pro nobis.\n"\
"Mater divinae gratiae, ora pro nobis.\n"\
"Mater purissima, ora pro nobis.\n"\
"Mater castissima, ora pro nobis.\n"\
"Mater inviolata, ora pro nobis.\n"\
"Mater intemerata, ora pro nobis.\n"\
"Mater immaculata, ora pro nobis.\n"\
"Mater amabilis, ora pro nobis.\n"\
"Mater admirabilis, ora pro nobis.\n"\
"Mater boni consilii, ora pro nobis.\n"\
"Mater Creatoris, ora pro nobis.\n"\
"Mater Salvatoris, ora pro nobis.\n"\
"Mater misericordiae, ora pro nobis.\n"\
"Virgo prudentissima, ora pro nobis.\n"\
"Virgo veneranda, ora pro nobis.\n"\
"Virgo praedicanda, ora pro nobis.\n"\
"Virgo potens, ora pro nobis.\n"\
"Virgo humillima, ora pro nobis.\n"\
"Virgo clemens, ora pro nobis.\n"\
"Virgo fidelis, ora pro nobis.\n"\
"Speculum iustitiae, ora pro nobis.\n"\
"Sedes sapientiae, ora pro nobis.\n"\
"Causa nostrae laetitiae, ora pro nobis.\n"\
"Vas spirituale, ora pro nobis.\n"\
"Vas honorabile, ora pro nobis.\n"\
"Vas insigne devotionis, ora pro nobis.\n"\
"Rosa mystica, ora pro nobis.\n"\
"Turris Davidica, ora pro nobis.\n"\
"Turris eburnea, ora pro nobis.\n"\
"Domus aurea, ora pro nobis.\n"\
"Foederis arca, ora pro nobis.\n"\
"Ianua caeli, ora pro nobis.\n"\
"Stella matutina, ora pro nobis.\n"\
"Salus infirmorum, ora pro nobis.\n"\
"Refugium peccatorum, ora pro nobis.\n"\
"Consolatrix afflictorum, ora pro nobis.\n"\
"Auxilium Christianorum, ora pro nobis.\n"\
"Regina Angelorum, ora pro nobis.\n"\
"Regina Patriarcharum, ora pro nobis.\n"\
"Regina Prophetarum, ora pro nobis.\n"\
"Regina Apostolorum, ora pro nobis.\n"\
"Regina Martyrum, ora pro nobis.\n"\
"Regina Confessorum, ora pro nobis.\n"\
"Regina Virginum, ora pro nobis.\n"\
"Regina Sanctorum omnium, ora pro nobis.\n"\
"Regina sine labe originali concepta, ora pro nobis.\n"\
"Regina in caelum assumpta, ora pro nobis.\n"\
"Regina sacratissimi Rosarii, ora pro nobis.\n"\
"Regina familiae, ora pro nobis.\n"\
"Regina pacis, ora pro nobis.\n"\
"Agnus Dei, qui tollis peccata mundi, parce nobis, Domine.\n"\
"Agnus Dei, qui tollis peccata mundi, exaudi nos, Domine.\n"\
"Agnus Dei, qui tollis peccata mundi, miserere nobis.\n"\
"\n"\
"V. Ora pro nobis, sancta Dei Genitrix,\n"\
"R. Ut digni efficiamur promissionibus Christi\n"\
"\n"\
"Concede nos famulos tuos, quaesumus,\n"\
"Domine Deus, perpetua mentis et corporis sanitate gaudere: et,\n"\
"gloriosa beatae Mariae semper Virginis intercessione,\n"\
"a praesenti liberari tristitia,\n"\
"et aeterna perfrui laetitia.\n"\
"Per Christum Dominum nostrum.\n"\
"Amen.\n"

const Params_data Litaniae::params_data = {
											Param_data("genus", typeid(const char*))
											};

std::string Litaniae::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	if(args.next() == "lauretanae")
		return LAURETANAE;
	else
		throw std::runtime_error("Genus Litaniarum non recognitum");
}
