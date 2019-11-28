// ########################################
/**
 * ÖTLET 2
 * Adjuk be a "viselkedést" ctorban a PersonWrapper-nek.
 * + Mockolható
 * + decoupled
 * ? A handle helyett azért tértem át az id használatra, mert ugyan
 *   overhead-et okoz, viszont biztonságosabb mert ezen a módon
 *   void ptr épp csak egy pillanatig van az én oldalamon...
 * - Ahhoz hogy ez az egész menjen kell dependency injection
 * - Személy szerint a PersonWrapper nekem már nem is kéne, csak az 
 *   emberek nagyon szeretik az objektumokat...
 */
class IPersonBehavior{
	
	virtual int load_by_name(const std::string&) const = 0;

	virtual std::string get_name(int) const = 0;

};


class PersonBehaviorReal : public IPersonBehavior{
	
	virtual int load_by_name(const std::string&s) const{
		Person p;
		if(load_person_by_name(&p, s.c_str()) !=0)
			throw std::runtime_error("C API err"); // err handling nem a kérdés tárgya
		int id = -1;
		if(person_get_id(p, &id !=0)
			throw std::runtime_error("C API err");
		return id;
	}
	
	virtual std::string get_name(int) const{ 
		/* ... annyi hogy itt először fetch_person_by_id-vel az int-hez tartozó handle-t előszedjük egy rövid időre */ 
	}
};


class PersonBehaviorMock : public IPersonBehavior{
/* ... */
};


class PersonWrapper{
	// ...Lifecycle-t most hagyjuk nem lényeg
	PersonWrapper(const std::string &s, const std::shared_ptr<IPersonBehavior> &b) : b_(b), id_(-1) {
		id_ = b_->load_by_name(s); // tovább delegáljuk a munkát
	}
	
	std::string get_name(){
		return b_->get_name(id_); // tovább delegáljuk a munkát
	}

private:

	std::shared_ptr<IPersonBehavior> b_;
	
	int id_;
};