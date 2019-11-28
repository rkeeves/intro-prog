// ########################################
/**
 * ÖTLET 1
 * Naív próbálkozásban simán az API felé rakunk egy class-t, ahogy az alább látható.
 * - Egyenesen hívjuk a C API-t szóval mockolhatatlan
 */
class PersonWrapperNaive{
public:
	// ...Lifecycle-t most hagyjuk nem lényeg
	PersonWrapperNaive(std::string) : person_handle_(nullptr) {
		if(load_person_by_name(person_handle_,s.c_str()) != 0)
			throw std::runtime_error("C API err"); // err handling nem a kérdés tárgya
	}
	
	std::string get_name(){
		// itt egyenesen hívnánk az API-t a handle-el stb...
	}

private:
	Person person_handle_;
};