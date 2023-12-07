Bu proje, çift yönlü bir bağlı liste olan `BiRing` sınıfının C++ dilinde implementasyonunu içermektedir. Bu veri yapısı, her düğümün bir anahtar (`Key`) ve bir bilgi (`Info`) tuttuğu, düğümlerin çift yönlü olarak birbirlerine bağlı olduğu bir veri yapısıdır.

Ayrıca, `BiRing` sınıfı için temel fonksiyonların testlerini içeren bir test paketi de bulunmaktadır. Bu testler, sınıfın temel işlevselliğini doğrulamak ve işlevlerin beklenen şekilde çalıştığını belirtmek amacıyla yazılmıştır.
2. Çift Yönlü Bağlı Liste (BiRing)

Çift yönlü bağlı liste, her düğümün bir önceki ve bir sonraki düğüme işaretçi içerdiği bir veri yapısıdır. `BiRing` sınıfı, bu yapıyı temsil eder ve aşağıdaki özelliklere sahiptir:

- **Düğüm (Node) Yapısı**: Anahtar (`Key`), Bilgi (`Info`), bir sonraki düğümün işaretçisi (`next`), bir önceki düğümün işaretçisi (`prev`) içeren bir yapı.
- **Baş ve Son İşaretçileri**: Liste başını (`head`) ve sonunu (`tail`) işaret eden işaretçiler.
- **Temel Fonksiyonlar**: Ekleme, çıkarma, ekleme, çıkarma, filtreleme, benzersiz öğeleri alma, karıştırma vb. işlemleri gerçekleştirebilen fonksiyonlar.

3. Kullanılan Veri Yapıları ve Teknolojiler

- **C++ Dilinde Yazılım**: Proje C++ programlama dilinde geliştirilmiştir.
- **Standart Kütüphaneler**: `iostream`, `unordered_map`, `vector`, `algorithm`, `functional` gibi standart kütüphaneler kullanılmıştır.
- **Çift Yönlü Bağlı Liste (BiRing) Sınıfı**: Ana `BiRing` sınıfı içinde, düğümlerin işlenmesini sağlayan metotlar bulunmaktadır.

4. BiRing Sınıfı Fonksiyonları ve Testleri

Projenin önemli fonksiyonları ve bunların test edilmiş halleri şunlardır:

- **`push_front`**: Listenin başına öğe ekleme işlemi. Test edilmiştir ve beklenen şekilde çalışmaktadır.
- **`pop_front`**: Listenin başından öğe çıkarma işlemi. Test edilmiştir ve beklenen şekilde çalışmaktadır.
- **`insert`**: Belirli bir konuma öğe ekleme işlemi. Test edilmiştir ve beklenen şekilde çalışmaktadır.
- **`erase`**: Belirli bir konumdaki öğeyi çıkarma işlemi. Test edilmiştir ve beklenen şekilde çalışmaktadır.
- **`filter`**: Belirli bir koşula göre öğeleri filtreleme işlemi. Test edilmiş ve beklenen şekilde çalışmaktadır.
- **`unique`**: Benzersiz öğeleri alma ve belirli bir işlevle birleştirme işlemi. Test edilmiş ve beklenen şekilde çalışmaktadır.
- **`shuffle`**: İki listenin belirli bir stratejiye göre karıştırılması işlemi. Test edilmiş ve beklenen şekilde çalışmaktadır.

5. Çalışmanın Sonucu

Proje, `BiRing` sınıfının çift yönlü bağlı listeyi başarılı bir şekilde temsil ettiğini göstermektedir. Tüm testler başarılı bir şekilde geçilmiş ve sınıfın işlevselliği doğrulanmıştır.
Bu çalışma, C++ dilinde çift yönlü bir bağlı liste olan `BiRing` sınıfının implementasyonunu ve bu sınıfın temel işlevlerini doğrulayan testleri içermektedir. Proje, çeşitli işlemleri gerçekleştirebilen esnek bir veri yapısını başarıyla göstermektedir.
