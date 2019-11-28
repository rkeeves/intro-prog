// ########################################
/**
 * KÉRDÉS
 * - Hogyan éri meg wrapper class-t csinálni legacy C API köré?
 * - A kérdés lényege, hogy a wrapper mockolhatóvá kell tenni (későbbi googletest és általános decoupling miatt)
 * - Nem akartam már bonyolítani, de nem ennyire egyszerű az API
 *   tele van igazi undorító C stílusú visit function-ökkel
 *   ezeket akarom lambdásítani. Ez a lambdásítás egyébként 
 *   az igazi oka annak hogy wrapper-t írjak.
 */
// API a valódi struct-okat hide-olja.
typedef void* Person;
typedef void* Organ;
// A szokásos user data megszokott C APIs módon, semmi új
typedef void* UserData;
// Person életciklusa a main C prog által menedzselt.
// Mi nem takarítjuk és nem inicializáljuk direktben.
extern int load_person_by_name(Person*,char*);
// Név getter
extern int person_get_name(Person,char**);
// Név setter
extern int person_set_name(Person,char*);
// Id getter. Ez nem a struct állapotváltozója, hanem egy fél-perzisztens azonosító.
// Fél perzisztens azért, mert addig tart amíg a C progi fut.
// Szóval egy felokosított futó sorszám.
// (Hosszú történet, de azért kell mert a main prog össze-vissza tölti be, írja ki lemezre,
// szóval a handle amit ad az csak addig megbízható amíg a mi callbackünkben vagyunk (mi dll-ként vagyunk betöltve a main progiba).)
extern int person_get_id(Person,int*);
// Ha az adott session ilyen id-hoz van Person, akkor vissza adja a handle-t.
extern int fetch_person_by_id(Person*,int);
// Undorító C-style visit func. 
// Ő meg a kisbarátja most nem a kérdés tárgya
// Csak megakartam jegyezni, hogy miattuk megy az egész wrapperelés :)
typedef int (*PersonOrganVisitFn) (Organ,UserData);
extern int DoPersonOrganVisit  (Person ,PersonOrganVisitFn ,UserData);