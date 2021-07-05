import styles from '../../styles/components/ButtonRegister.module.css'
import Swal from 'sweetalert2'

export function ButtonRegister(){
    var name = "";
    function Cadastrar(){
      Swal.fire({
        html:`
          <div class=${styles.cadastroAlert}>
              <h1>Digite o nome do petiano</h1>
          </div>        
        `,
        customClass: `${styles.boxCadastro}`,
        input: 'text',          
        inputValidator: function(value) {               
          if (!value) {
            return('Insira um nome :)');
          }              
        },
        inputAttributes: {
          autocapitalize: 'off'
        },
        showCloseButton: true,
        background: '#192734',    
        backdrop: 'rgba(0,0,0,0.7)',
        confirmButtonText: 'Cadastrar',
        confirmButtonColor:'#17A2B8' ,
        showLoaderOnConfirm: true,
        preConfirm: (login) => {
            name = login;
                
        },      
        allowOutsideClick: () => !Swal.isLoading()
      }).then((result)=>{
        if (result.isConfirmed) { 
          const Toast = Swal.mixin({
            toast: true,
            position: 'top-end',
            showConfirmButton: false,
            timer: 3000,
            timerProgressBar: true,
            didOpen: (toast) => {
              toast.addEventListener('mouseenter', Swal.stopTimer)
              toast.addEventListener('mouseleave', Swal.resumeTimer)
            }
          })                    
          Toast.fire({
            icon: 'success',
            title: `${result.value} cadastrado com sucesso`
          })                
        }         
      })        
    }
    
    return(
        <div>
            <button onClick={Cadastrar} className={styles.cadastrar}>CADASTRAR PETIANO</button>
        </div>
    )
}