import styles from '../../styles/components/UserBox.module.css'
import { FiTrash2, FiPlus } from 'react-icons/fi';
import { CardButton } from '../../components/CardButton/CardButton'
import { useEffect } from 'react'
import Aos from 'aos'
import "aos/dist/aos.css"
import Swal from 'sweetalert2'
import socket from '../../services/socketio';

export function UserBox(props){
    useEffect(() => {
        Aos.init({ duration: 2000})
      }, [])


      function Delete(){
        Swal.fire({
            title: 'Deletar Petiano',
            text: 'Tem certeza que quer deletar este petiano?',
            showCancelButton: true,
            customClass: `${styles.boxCadastroDados}`,
            background: '#192734',
            backdrop: 'rgba(0,0,0,0.7)',
            confirmButtonColor: '#17A2B8',
            cancelButtonColor: '#EE2E2E',
            confirmButtonText: 'Sim'
          }).then( async (result) => {
            if (result.isConfirmed) {
                socket.emit("delete_user", props.id);
            }
        })      
    }

    return(
        <div data-aos="zoom-in" className={styles.container}>
            <div className={styles.boxHeader}>
                <h2>{props.name}</h2>

                <div onClick={Delete} className={styles.boxHeaderIcons}>
                    <FiTrash2 size="2.1rem" strokeWidth="0.9px" color="#8899A6"/>
                </div>
            </div>

            <div className={styles.boxBody}>
                <p> Biometria: </p> 
                <div className={styles.boxIcons}>
                    <CardButton id={props.id} icon={"add"} type={"biometria"}/>
                    
                    {props.biometry !== -1 && <CardButton id={props.id} icon={"del"} type={"biometria"}/>}
                    
                </div>

                <p> Cartão: </p> 
                <div className={styles.boxIcons}>
                    <CardButton id={props.id} icon={"add"} type={"cartao"}/>
                    
                    {props.card !== null && <CardButton id={props.id} icon={"del"} type={"cartao"}/>}
                </div>
            </div>            

        </div>
    )
}