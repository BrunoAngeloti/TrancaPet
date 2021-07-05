import { FiTrash2, FiPlus } from 'react-icons/fi';
import styles from '../../styles/components/CardButton.module.css'
import Swal from 'sweetalert2'

export function CardButton(props){

    function Cadastra(){
        Swal.fire({
            title: `Cadastrar ${props.type}`,
            text: `Tem certeza que quer cadastrar ${props.type === 'biometria' ? 'uma' : 'um' } ${props.type}?`,
            showCancelButton: true,
            customClass: `${styles.boxCadastroDados}`,
            background: '#192734',
            backdrop: 'rgba(0,0,0,0.7)',
            confirmButtonColor: '#17A2B8',
            cancelButtonColor: '#EE2E2E',
            confirmButtonText: 'Sim'
          }).then( async (result) => {
            if (result.isConfirmed) {
                Swal.fire({
                    title: `Aguardando cadastro ${props.type}`,
                    customClass: `${styles.boxCadastroDados}`,
                    background: '#192734',
                    allowOutsideClick: false,
                    showCloseButton: true,
                    showConfirmButton: false,
                    showCancelButton: false,
                    showDenyButton: false,
                    didOpen: () => {
                        Swal.showLoading()
                        const timerInterval = setInterval(() => {
                          const content = Swal.getHtmlContainer()
                          if (content) {
                            const b = content.querySelector('b')
                            if (b) {
                              b.textContent = Swal.getTimerLeft()
                            }
                          }
                        }, 100)
                      },
                     
                
                })
            }
        })
    }

    function Delete(){
        Swal.fire({
            title: `Deletar ${props.type}`,
            text: `Tem certeza que quer deletar ${props.type === 'biometria' ? 'a' : 'o' } ${props.type}?`,
            showCancelButton: true,
            customClass: `${styles.boxCadastroDados}`,
            background: '#192734',
            backdrop: 'rgba(0,0,0,0.7)',
            confirmButtonColor: '#17A2B8',
            cancelButtonColor: '#EE2E2E',
            confirmButtonText: 'Sim'
          }).then( async (result) => {
            if (result.isConfirmed) {
                Swal.fire({
                    toast: true,
                    position: 'top-end',
                    showConfirmButton: false,
                    timer: 3000,
                    timerProgressBar: true,
                    didOpen: (toast) => {
                        toast.addEventListener('mouseenter', Swal.stopTimer)
                        toast.addEventListener('mouseleave', Swal.resumeTimer)
                    },
                    icon: 'error',
                    title: `${props.type} ${props.type === 'biometria' ? 'deletada' : 'deletado' } com sucesso`
                })
            }
        })      
    }


    return(
        props.icon == 'add' ?
            <div onClick={Cadastra} className={styles.cardPlus}>
                <FiPlus size="2.1rem" strokeWidth="0.9px"/>
            </div>
        :
            <div onClick={Delete} className={styles.cardDel}>
                <FiTrash2 size="2rem" color="white" strokeWidth="0.8px"/>
            </div>
    )
}